#include <iostream>
#include <assert.h>

#include "TutoSurface.h"
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

extern __global__ void KSeuillageSurf(cudaSurfaceObject_t surf2d, uchar* tabPixelVideoGM , uint w , uint h , uchar seuil0255);
extern __global__ void KDilatationSurf(uchar* tabPixelsGM , cudaSurfaceObject_t surf2d , uint w , uint h);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

TutoSurface::TutoSurface(const Grid& gridDilatation , IteratorImageGray_I* ptrIteratorImage , uint seuil0255) :
	Animable_I<uchar>(gridDilatation, ptrIteratorImage->getW(), ptrIteratorImage->getH(), "Tuto_surface_uchar"), //
//
	ptrIteratorImage(ptrIteratorImage), //
//
	gridSeuillage(bestGridSeuillage()), //
	gridDilatation(gridDilatation), //
//
	wh(ptrIteratorImage->getWH()), seuil0255(seuil0255), //
//
	surface2D(ptrIteratorImage->getW(), ptrIteratorImage->getH(),CudaArrayType::SURFACE_LOAD_STORE) // SURFACE_LOAD_STORE DEFAULT_CUARRAY
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

TutoSurface::~TutoSurface()
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
void TutoSurface::process(uchar* tabPixelsGM , uint w , uint h , const DomaineMath& domaineMath)
    {
    //                cpyHtoD                    seuillage             dilatation
    // tabPixelVideo --------->  tabPixelVideoGM ----------> surface2D ---------> tabPixelGM
    //                                          write Surface          read Surface
    //                Etape 1                    Etape 2               Etape 3

    // Etape 1
    GM::memcpyHToD(tabPixelVideoGM, tabPixelVideo, sizeImage);

    // Etape 2
    KSeuillageSurf<<<gridSeuillage.dg,gridSeuillage.db>>>(surface2D.surfCuda , tabPixelVideoGM,w,h, seuil0255);

    // Etape 3
    KDilatationSurf<<<gridDilatation.dg,gridDilatation.db>>>(tabPixelsGM ,surface2D.surfCuda, w , h);
    }

/**
 * Override
 * Call periodicly by the API
 */
void TutoSurface::animationStep()
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
Grid TutoSurface::bestGridSeuillage()
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    dim3 dg(MP * 2);
    dim3 db(CORE_MP * 8);
    Grid gridConstrastor(dg, db);

    return gridConstrastor;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

