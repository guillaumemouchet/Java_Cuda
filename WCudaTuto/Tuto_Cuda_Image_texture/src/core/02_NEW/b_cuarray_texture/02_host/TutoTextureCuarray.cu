#include <iostream>
#include <assert.h>

#include "TutoTextureCuarray.h"
#include "GM.h"
#include "Hardware.h"

#include "OpencvTools_GPU.h"

using std::cout;
using std::cerr;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void KSeuillage(uchar* tabPixelVideoGM , uint wh , uint seuil0255);
extern __global__ void kDilatationTex(uchar* tabPixelsGM , cudaTextureObject_t tex2dGM , uint w , uint h);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

TutoTextureCuarray::TutoTextureCuarray(const Grid& gridDilatation , IteratorImageGray_I* ptrIteratorImage , uint seuil0255) :
	Animable_I<uchar>(gridDilatation, ptrIteratorImage->getW(), ptrIteratorImage->getH(), "Tuto_texture_uchar"), //
//
	ptrIteratorImage(ptrIteratorImage), //
//
	gridSeuillage(bestGridSeuillage()), //
	gridDilatation(gridDilatation), //
//
	wh(ptrIteratorImage->getWH()), seuil0255(seuil0255), //
//
	texture2DVideo(ptrIteratorImage->getW(), ptrIteratorImage->getH())
    {
    // Tools
    this->t = 0; // protected dans Animable

    // MM
	{
	this->sizeImage = sizeof(uchar) * wh;
	GM::malloc(&tabPixelVideoGM, sizeImage);
	}

    //video
	{
	this->tabPixelVideo = ptrIteratorImage->first();
	}
    }

TutoTextureCuarray::~TutoTextureCuarray()
    {
    GM::free(tabPixelVideoGM);
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
void TutoTextureCuarray::process(uchar* tabPixelsGM , uint w , uint h , const DomaineMath& domaineMath)
    {
    //                cpyHtoD                    seuillage                     cpyDtoD             dilatation
    // tabPixelVideo --------->  tabPixelVideoGM ----------> tabPixelVideoGM ----------> texture2D ---------> tabPixelGM
    //  								                          read Texture
    //		      Etape 1			   Etape 2             Etape 3                    Etape 4

    // Etape 1
    GM::memcpyHToD(tabPixelVideoGM, tabPixelVideo, sizeImage);

    // Etape 2
    KSeuillage<<<gridSeuillage.dg,gridSeuillage.db>>>(tabPixelVideoGM , wh, seuil0255);

    // Etape 3
    texture2DVideo.memcpyDtoD(tabPixelVideoGM);

    // Etape 4
    kDilatationTex<<<gridDilatation.dg,gridDilatation.db>>>(tabPixelsGM , texture2DVideo.texCuda, w , h);
    }

/**
 * Override
 * Call periodicly by the API
 */
void TutoTextureCuarray::animationStep()
    {
    t++;

    this->tabPixelVideo = ptrIteratorImage->next();
    }

/*-------------------------*\
 |*	private		    *|
 \*-------------------------*/

/**
 * static
 */
Grid TutoTextureCuarray::bestGridSeuillage()
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    dim3 dg(MP * 8);
    dim3 db(CORE_MP * 2);
    Grid gridConstrastor(dg, db);

    return gridConstrastor;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

