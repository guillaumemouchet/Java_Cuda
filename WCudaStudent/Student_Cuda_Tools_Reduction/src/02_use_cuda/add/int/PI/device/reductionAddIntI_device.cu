#include "Thread1D.cu.h"
#include "cudas.h"

#include "ReductionAdd.cu.h"

#include <stdio.h>

/*----------------------------------------------------------------------*\
 |*            Declaration                     *|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*        Private            *|
 \*-------------------------------------*/

static __device__ void reductionIntraThread(int* tabSM);

/*----------------------------------------------------------------------*\
 |*            Implementation                     *|
 \*---------------------------------------------------------------------*/

__global__ void KAddIntProtocoleI(int* ptrSumGM)
    {
    // TODO ReductionAddIntI

    // R?ception ("D?claration") tabSM
    extern __shared__ int tabSM[];

    // ReductionIntraThread
    reductionIntraThread (tabSM);
    __syncthreads(); // Attention, selon la taille de la grille le code peut quand meme fonctionner
    // ReductionAdd
    ReductionAdd::reduce(tabSM, ptrSumGM);
//    __syncthreads(); // des threads de meme block!// Question : utile? ou?
    }

/*--------------------------------------*\
 |*        	  Private               *|
 \*-------------------------------------*/

/**
 * 1 partout en tabSM
 */
__device__ void reductionIntraThread(int* tabSM)
    {
    // TODO ReductionAddIntI
    const int TID_LOCAL = Thread2D::tidLocalBlock();
    tabSM[TID_LOCAL] = 1;
    }

/*----------------------------------------------------------------------*\
 |*            End                         *|
 \*---------------------------------------------------------------------*/
