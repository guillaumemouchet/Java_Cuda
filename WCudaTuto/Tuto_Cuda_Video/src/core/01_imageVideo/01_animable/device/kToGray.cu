#include "Thread2D.cu.h"
#include "cudas.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		private			*|
 \*-------------------------------------*/

static __device__ void toGray(uchar4* pixel);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

__global__ void kToGray(uchar4* tabPixelsGM , uint wh)
    {
    const int TID = Thread2D::tid();
    const int NB_THREAD = Thread2D::nbThread();

    int s = TID;
    while (s < wh)
	{
	toGray(&tabPixelsGM[s]); //update color

	s += NB_THREAD;
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ void toGray(uchar4* ptrPixelColor)
    {
    const float POIDS=1.0f/3.0f;

    uchar r = ptrPixelColor->x;
    uchar g = ptrPixelColor->y;
    uchar b = ptrPixelColor->z;

    uchar levelGris = r * POIDS + g * POIDS + b * POIDS;

    ptrPixelColor->x = levelGris;
    ptrPixelColor->y = levelGris;
    ptrPixelColor->z = levelGris;

    ptrPixelColor->w = 255; // opaque
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

