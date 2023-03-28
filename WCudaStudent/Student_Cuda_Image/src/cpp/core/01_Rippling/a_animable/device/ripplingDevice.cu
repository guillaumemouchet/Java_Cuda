#include "Thread2D.cu.h"
#include "Thread1D.cu.h"
#include "cudas.h"

#include "Indices.cu.h"

#include "RipplingMath.cu.h"


/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

__global__ void rippling(uchar4* tabPixelsGM , uint w , uint h , float t)
    {
    // DONE instacier RipplingMath

    RipplingMath rm(w,h,t);

    const int TID = Thread2D::tid();
    const int NB_THREAD = Thread2D::nbThread();
    const int WH = w * h;
    int s = TID;
    int i;
    int j;
    // Notre image est unidimenstionnel entre 0 et WH-1
    // i [0,h[
    // j [0,w[
    // DONE Rippling GPU  pattern entrelacement
    while(s<WH)
	{
	Indices::toIJ(s, w, &i, &j);
	rm.colorIJ(&tabPixelsGM[s], i, j);
	s+=NB_THREAD;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

