#include <iostream>
#include <assert.h>

#include "TutoTextureGM.h"
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

extern __global__ void KSeuillage(uchar* tabPixelsSeuillerGM , uint wh , uint seuil0255);
extern __global__ void kDilatationTex(uchar* tabPixelsGM , cudaTextureObject_t tex2dGM , uint w , uint h);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

TutoTextureGM::TutoTextureGM(const Grid& gridDilatation , IteratorImageGray_I* ptrIteratorImage , uint seuil0255) :
	Animable_I<uchar>(gridDilatation, ptrIteratorImage->getW(), ptrIteratorImage->getH(), "Tuto_texture_GM_uchar"), //
//
	ptrIteratorImage(ptrIteratorImage), //
//
	gridSeuillage(bestGridSeuillage()), //
	gridDilatation(gridDilatation), //
	//
	wh(ptrIteratorImage->getWH()), seuil0255(seuil0255), //
//
	texture2D_GM(ptrIteratorImage->getW(), ptrIteratorImage->getH())
    {
    // Tools
    this->t = 0; // protected dans Animable

    // MM
	{
	this->sizeImage = sizeof(uchar) * wh;
	GM::malloc(&tabPixelSeuillerGM, sizeImage);
	}
    //video
	{
	this->tabPixelVideo = ptrIteratorImage->first();
	}
    }

TutoTextureGM::~TutoTextureGM()
    {
    GM::free(tabPixelSeuillerGM);
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
void TutoTextureGM::process(uchar* tabPixelsGM , uint w , uint h , const DomaineMath& domaineMath)
    {
    //                cpyHtoD                         seuillage                       lunette                dilatation
    // tabPixelVideo --------->  tabPixelsSeuillerGM  ----------> tabPixelsSeuillerGM --------> texture2D_GM---------> tabPixelGM
    //						                                                             read texture
    //               Etape 1                           Etape 2                        Etape 3                Etape 4

    // Etape 1
    GM::memcpyHToD(tabPixelSeuillerGM, tabPixelVideo, sizeImage);

    // Etape 2
    KSeuillage<<<gridSeuillage.dg,gridSeuillage.db>>>(tabPixelSeuillerGM , wh, seuil0255);

    // Etape 3
    texture2D_GM.see(tabPixelSeuillerGM);

    // Etape 4
    kDilatationTex<<<gridDilatation.dg,gridDilatation.db>>>(tabPixelsGM , texture2D_GM.texCuda , w , h);
    }

/**
 * Override
 * Call periodicly by the API
 */
void TutoTextureGM::animationStep()
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
Grid TutoTextureGM::bestGridSeuillage()
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    dim3 dg(MP * 2);
    dim3 db(CORE_MP * 7);
    Grid gridConstrastor(dg, db);

    return gridConstrastor;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

