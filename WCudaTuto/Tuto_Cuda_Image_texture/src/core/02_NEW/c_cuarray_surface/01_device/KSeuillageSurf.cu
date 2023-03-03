#include "Thread2D.cu.h"
#include "Thread1D.cu.h"
#include "cudas.h"
#include "Maths.h"

#include "Calibreur.cu.h"
#include "Indices.cu.h"
#include "ifelse.cu.h"


/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/
/**
 * tabPixelGM   : read
 * surf2d       : write
 */
__global__ void KSeuillageSurf(cudaSurfaceObject_t surf2d, uchar* tabPixelVideoGM , uint w , uint h , uchar seuil0255)
    {
    const int WH = w * h;
    const int TID = Thread2D::tid();
    const int NB_THREAD = Thread2D::nbThread();

    int s = TID;
    int i;
    int j;
    uchar pixelS;
    while (s < WH)
	{
	Indices::toIJ(s, w, &i, &j);

	// read
	pixelS = tabPixelVideoGM[s];

	// work
	pixelS = ifelse(pixelS < seuil0255, 0, 255);

	// write
	surf2Dwrite(pixelS, surf2d, j, i); // warning : (j,i) et non (j,i)

	// next
	s += NB_THREAD;
	}
    }


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

