#include "DamierHueFloat.h"

#include <iostream>
#include <assert.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

__global__ void damierHueFloat(float* tabPixelsGM , uint w , uint h , DomaineMath domaineMath , uint n , float t);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

DamierHueFloat::DamierHueFloat(const Grid& grid , uint w , uint h , float dt , uint n , const DomaineMath& domaineMath,bool isVerbose) :
	Animable_I<float>(grid, w, h, "Damier-Cuda-Hue-float", domaineMath,isVerbose), //
	variateurAnimation(Interval<float>(0, 2 * PI), dt), //
	n(n)
    {
    // Tools
    this->t = 0;  // protected dans Animable
    }

DamierHueFloat::~DamierHueFloat()
    {
    // rien
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 */
void DamierHueFloat::process(float* tabPixelsGM , uint w , uint h , const DomaineMath& domaineMath)
    {
damierHueFloat<<<dg,db>>>(tabPixelsGM,w,h,domaineMath,n,t);
}

/**
 * Override
 * Call periodicly by the API
 */
void DamierHueFloat::animationStep()
{
this->t = variateurAnimation.varierAndGet(); // in [0,2pi]
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

