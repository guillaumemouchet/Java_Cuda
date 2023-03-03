#pragma once

#include <math.h>
#include "Maths.h"

#include "Colors.cu.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class VagueGrayMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ VagueGrayMath(int w , int h , int t) :
		h(h), //
		t(t)
	    {
	    // rien
	    }

	// constructeur copie automatique car pas pointeur dans VagueMath

	__device__
	     virtual ~VagueGrayMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__inline__
	__device__
	void colorIJ(uchar* ptrLevelGris , int i , int j )
	    {
	    *ptrLevelGris = 255.f * (i + t) / (float)h;
	    }

    private:

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	int h;
	int t;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
