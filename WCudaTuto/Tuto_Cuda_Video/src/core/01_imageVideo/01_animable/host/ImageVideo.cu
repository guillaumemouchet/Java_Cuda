#include <iostream>
#include <assert.h>

#include "ImageVideo.h"
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

ImageVideo::ImageVideo(const Grid& grid , uint w , uint h , string nameVideo , int nbImage) :
	Animable_I<uchar4>(grid, w, h, "Video_RGBA_uchar4"), //
	videoProviderRGB(nameVideo, nbImage)
    {
    // Tools
    this->t = 0; // protected dans Animable
    this->sizeImage = sizeof(uchar4) * w * h;

    //video
	{
	bool isOk = videoProviderRGB.loadALL();
	assert(isOk);
	assert(videoProviderRGB.getW() == w && videoProviderRGB.getH() == h);

	animationStep();
	}
    }

ImageVideo::~ImageVideo()
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
void ImageVideo::process(uchar4* tabPixelsGM , uint w , uint h , const DomaineMath& domaineMath)
    {
    GM::memcpyHToD(tabPixelsGM, ptrTabPixelVideo, sizeImage);

    kToGray<<<dg,db>>>(tabPixelsGM, w * h);
    }

/**
 * Override
 * Call periodicly by the API
 */
void ImageVideo::animationStep()
    {
    t++;

    this->ptrTabPixelVideo = videoProviderRGB.getImage();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

