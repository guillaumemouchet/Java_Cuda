#include "Thread2D.cu.h"
#include "Thread1D.cu.h"
#include "ReductionAdd.cu.h"

#include "cudas.h"

#include <stdio.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static __device__ void reductionIntraThread(float* tabSM,int nbSlice);
static __device__ float f(float x);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

__global__ void sliceSM(int nbSlice , float* ptrPiHatGM)
    {
    // TODO SliceSM

    extern __shared__ float tabSM[];

    reductionIntraThread(tabSM, nbSlice);
    __syncthreads();
    ReductionAdd::reduce(tabSM, ptrPiHatGM);
    // Declarer tabSM
    // ReductionIntraThread
    // Reduction de tabSM (use tools ReductionAdd)

    // __syncthreads(); necessaire? ou?
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * remplit la sm
 */
__device__ void reductionIntraThread(float* tabSM , int nbSlice)
    {
    // TODO SliceSM
    const float DX = 1 / (float)nbSlice;
    const int NB_THREADS = Thread2D::nbThread();
    const int TID = Thread2D::tid();
    const int TID_LOCAL = Thread2D::tidLocalBlock();

    int s = TID;
    float sumThread = 0;

    while (s < nbSlice)
    {
	sumThread += f(s * DX);

	s += NB_THREADS;
    }
    tabSM[TID_LOCAL] = sumThread;
    // Warning: Il faut employer TID et TID_LOCAL
    }

__device__ float f(float x)
    {
    return 4.0f / (1.0f + x * x);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

