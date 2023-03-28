#pragma once

#include <math.h>
#include "Maths.h"

#include "Colors.cu.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RipplingMath
    {
	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	__device__ RipplingMath(uint w , uint h,float t) :
		dim2(w / 2),//
		t(t)
	    {
	    // rien
	    }

	__device__
	      virtual ~RipplingMath(void)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorIJ(uchar4* ptrColorIJ , int i , int j )
	    {
	    uchar levelGris;

	    levelGray(i,j, &levelGris); // update levelGris

	    ptrColorIJ->x = levelGris;
	    ptrColorIJ->y = levelGris;
	    ptrColorIJ->z = levelGris;

	    ptrColorIJ->w = 255; //opaque

	    // Conseil:
	    // 		Etape 1 : 	Commencer par afficher une image uniforme grise (128 par exemple)
	    // 				pour valider tout le pipeline en amont
	    //
	    // 		Etape 2:	Puis une fois que l'image grise est valider, attaquer rippling

	    //debug temp
//	    		{
//	    		ptrColorIJ->x = 128;
//	    		ptrColorIJ->y = 128;
//	    		ptrColorIJ->z = 128;
//	    		ptrColorIJ->w = 255; // opacity facultatif
//	    		}
	    }

    private:

	__inline__
	__device__
	void levelGray(int i , int j ,  uchar* ptrLevelGray)
	    {
	    float dij10;
	    dij(i, j, &dij10); // warning : dij return void. Ne peut pas etre "imbriquer dans une fonction"
	    dij10 = dij10 / 10.f;
	    float numerator = cosf(dij10- t/7);
	    float denominator =  dij10 + 1;

	    *ptrLevelGray = (128 + 127 * (numerator/denominator));
	    // DONE Rippling GPU : cf formules math rippling.pdf
	    }

	__inline__
	__device__
	void dij(int i , int j , float* ptrResult)
	    {
	    //TODO Rippling GPU cf fonction math pdf
	    float fi = i - dim2;
	    float fj = j -dim2;

	    *ptrResult = sqrt(fi*fi+fj*fj);
	    // Ne pas utiliser la fonction pow pour elever au carrer !
	    // Utiliser l'opérateur *
	    }

	/*--------------------------------------*\
	|*		Attribut			*|
	 \*-------------------------------------*/

    private:

	// Tools
	int dim2;	    // dim2=dim/2
	float t;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
