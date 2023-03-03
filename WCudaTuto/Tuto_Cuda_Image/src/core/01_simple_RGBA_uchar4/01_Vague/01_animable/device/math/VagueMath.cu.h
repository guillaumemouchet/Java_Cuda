#pragma once

#include <math.h>
#include "Maths.h"

#include "Colors.cu.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class VagueMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ VagueMath(int w , int h, int t) :
		h(h),//
		t(t)
	    {
	    //rien
	    }

	// constructeur copie automatique car pas pointeur dans VagueMath

	__device__
	      virtual ~VagueMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorIJ(uchar4* ptrColor , int i , int j )
	    {
	    uchar levelGris;

	    levelGray(&levelGris, i, j); // update levelGris

	    ptrColor->x = levelGris;
	    ptrColor->y = levelGris;
	    ptrColor->z = levelGris;

	    ptrColor->w = 255; // opaque
	    }

    private:

	__inline__
	__device__
	void levelGray(uchar* ptrLevelGris , int i , int j )
	    {
	    *ptrLevelGris = 255.f * (i + t) / (float)h;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	int h;
	int t;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
