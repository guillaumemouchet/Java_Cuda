#include <iostream>
#include <assert.h>

#include "ImageFile.h"
#include "GM.h"

using std::cout;
using std::cerr;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void kToGray(uchar4* tabPixelGM,uint wh);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

ImageFile::ImageFile(const Grid& grid , Image& image) :
	Animable_I<uchar4>(grid, image.w(), image.h(), "ImageFile_RGBA_uchar4"), //
	image(image)
    {
    // Tools
    this->t = 0; // protected dans Animable
    this->sizeImage = sizeof(uchar4) * w * h;

    this->ptrTabPixelImage = image.uchar4_RGBA();
    }

ImageFile::~ImageFile()
    {
    // rien
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 *
 * Note : domaineMath pas use car pas zoomable
 */
void ImageFile::process(uchar4* tabPixelsGM , uint w , uint h , const DomaineMath& domaineMath)
    {
    GM::memcpyHToD(tabPixelsGM, ptrTabPixelImage, sizeImage);

kToGray<<<dg,db>>>(tabPixelsGM, w * h);
}

/**
 * Override
 * Call periodicly by the API
 */
void ImageFile::animationStep()
{
t++;
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

