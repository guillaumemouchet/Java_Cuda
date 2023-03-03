#include "VagueGray.h"

#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void vagueGray(uchar* tabPixelsGM,uint w, uint h,int t);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

VagueGray::VagueGray(const Grid& grid , uint w , uint h , int dt,bool isVerbose) :
	Animable_I<uchar>(grid, w, h, "Vague-Cuda-GRAY-uchar",isVerbose), //
	dt(dt)
    {
    // Tools
    this->t = 0; // protected dans Animable
    }

VagueGray::~VagueGray()
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
void VagueGray::process(uchar* tabPixelsGM , uint w , uint h , const DomaineMath& domaineMath)
    {
vagueGray<<<dg,db>>>(tabPixelsGM,w,h,t);
}

/**
 * Override
 * Call periodicly by the API
 */
void VagueGray::animationStep()
{
t += dt;
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

