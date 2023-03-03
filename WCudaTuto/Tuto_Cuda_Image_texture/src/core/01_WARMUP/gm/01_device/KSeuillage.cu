#include "Thread2D.cu.h"
#include "Thread1D.cu.h"
#include "cudas.h"
#include "Maths.h"
#include "ifelse.cu.h"


/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

__global__ void KSeuillage(uchar* tabPixelVideoGM , uint wh , uint seuil0255)
    {
    const int TID = Thread2D::tid();
    const int NB_THREAD = Thread2D::nbThread();

    int s = TID;
    while (s < wh)
	{
	//v1
//	{
//	if ( tabPixelsGM[s] > seuil0255)
//	    {
//	    tabPixelsGM[s] = 255
//	    }
//	else
//	    {
//	    tabPixelsGM[s] = 0;
//	    }
//	}

	// v2
	tabPixelVideoGM[s] = ifelse(tabPixelVideoGM[s] > seuil0255,255,0);

	s += NB_THREAD;
	}
    }

/*----------------------------------------------------------------------*\
 |*			 private					*|
 \*---------------------------------------------------------------------*/

/**
 * Supression thread divergence:
 *
 * 	if (t)
 * 		return a;
 * 	else
 * 		return b;
 *
 * qui est identique a a thread divergence de l'operateur ternaire
 *
 * 	return t?a:b
 */
//__device__ uchar ifelse(uchar t , uchar a , uchar b)
//    {
//    return (1 - t) * b + t * a;
//    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

