#include "Thread2D.cu.h"
#include "cudas.h"

#include "DamierHueFloatMath.cu.h"

#include "Indices.cu.h"
#include "DomaineMath.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void damierHueFloat(float* tabPixelsGM , uint w , uint h , DomaineMath domaineMath , uint n , float t);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void damierHueFloat(float* tabPixelsGM , uint w , uint h , DomaineMath domaineMath , uint n , float t)
    {
    DamierHueFloatMath damierHueFloatMath(n,t);

    const int TID = Thread2D::tid();
    const int NB_THREAD = Thread2D::nbThread();
    const int WH = w * h;

    double x;
    double y;

    int i; // in [0,h[
    int j; // in [0,w[

    int s = TID;
    while (s < WH)
	{
	Indices::toIJ(s, w, &i, &j); // update (i, j)

	// (i,j) domaine ecran
	// (x,y) domaine math
	domaineMath.toXY(i, j, &x, &y); //  (i,j) -> (x,y)

	damierHueFloatMath.colorXY(&tabPixelsGM[s], x, y); // update ptrDevPixels[s]

	s += NB_THREAD;
	}

    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

