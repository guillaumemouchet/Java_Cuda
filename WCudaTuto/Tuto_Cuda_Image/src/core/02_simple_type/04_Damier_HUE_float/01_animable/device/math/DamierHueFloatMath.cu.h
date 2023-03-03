#pragma once

#include <math.h>

//#include "Calibreur.cu.h"
#include "Colors.cu.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class DamierHueFloatMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ DamierHueFloatMath(int n , float t) :
		//calibreur(Interval<float>(-1.f, 1.f), Interval<float>(0.f, 1.f)), //
		n(n), //
		t(t)
	    {
	    // rien
	    }

	// constructeur copie automatique car pas pointeur dans
	//	DamierMath
	// 	calibreur
	// 	IntervalF

	__device__
		      virtual ~DamierHueFloatMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorXY(float* ptrColor , float x , float y)
	    {
	    float z = f(x, y); // in [-1,1]

	    // v1
	    float hue01 = (z + 1)/2.f; // in [0,1]

	    // v2
	    // float hue01 = z;
	    // calibreur.calibrer(&hue01);// in [0,1]

	    *ptrColor = hue01;
	    }

    private:

	__inline__
	__device__
	float f(float x , float y )
	    {
	    return sinf(x * n + t) * cosf(y * n + t);
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	int n;
	float t;

	// Tools
	//Calibreur<float> calibreur;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
