#include <iostream>
#include <assert.h>

#include "Warmup.h"
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
extern __global__ void kDilatation(uchar* tabPixelsGM , uchar* tabPixelVideoSeuillerGM , uint w , uint h);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

Warmup::Warmup(const Grid& gridDilatation , IteratorImageGray_I* ptrIteratorImage,uint seuil0255) :
	Animable_I<uchar>(gridDilatation, ptrIteratorImage->getW(), ptrIteratorImage->getH(), "Warmup_dilatation_uchar"), //
	//
	ptrIteratorImage(ptrIteratorImage),	//
	//
	gridSeuillage(bestGridSeuillage()), //
	gridDilatation(gridDilatation), //
		//
	wh(ptrIteratorImage->getWH()),
	//
	seuil0255(seuil0255)
    {
    // Tools
    this->t = 0; // protected dans Animable

    // MM
	{
	this-> sizeImage = sizeof(uchar) * wh;
	GM::malloc(&tabPixelSeuillerGM, sizeImage);
	}

    //video
	{
	this->tabPixelVideo = ptrIteratorImage->first();
	}
    }

Warmup::~Warmup()
    {
    GM::free (tabPixelSeuillerGM);
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
void Warmup::process(uchar* tabPixelsGM , uint w , uint h , const DomaineMath& domaineMath)
    {
    //                cpyHtoD                         seuillage                      dilatation
    // tabPixelVideo --------->  tabPixelsSeuillerGM ----------> tabPixelsSeuillerGM ---------> tabPixelGM
    //		      Etape 1                         Etape 2                        Etape 3

    // Etape 1
    GM::memcpyHToD(tabPixelSeuillerGM, tabPixelVideo, sizeImage);

    // Etape 2
    KSeuillage<<<gridSeuillage.dg,gridSeuillage.db>>>(tabPixelSeuillerGM , wh,  seuil0255);

    // Etape 3
    kDilatation<<<gridDilatation.dg,gridDilatation.db>>>(tabPixelsGM , tabPixelSeuillerGM , w , h);
    }

/**
 * Override
 * Call periodicly by the API
 */
void Warmup::animationStep()
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
Grid Warmup::bestGridSeuillage()
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    dim3 dg(MP * 1);
    dim3 db(1024);
    Grid gridConstrastor(dg, db);

    return gridConstrastor;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

