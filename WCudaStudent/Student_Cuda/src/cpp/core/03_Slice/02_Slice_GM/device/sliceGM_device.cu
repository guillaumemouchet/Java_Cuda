#include <stdio.h>
#include <Thread2D.cu.h>

/*----------------------------------------------------------------------*\
 |*            Declaration                     *|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*        Private            *|
 \*-------------------------------------*/

static __device__ float f(float x);

/*----------------------------------------------------------------------*\
 |*            Implementation                     *|
 \*---------------------------------------------------------------------*/

/**
 * <pre>
 * Chaque thread effecteur une reduction intrathread avec le patern d'entrelacement,
 * puis stocke son r?sultat dans SA case dans tabGM
 *
 * tabGM est un tableau promu, qui a autant de case que de thread
 * </pre>
 */
__global__ void reductionIntraThreadGM(float* tabGM , int nbSlice)
    {
    const double DX = 1 / (double)nbSlice;
    const int NB_THREADS = Thread2D::nbThread();
    const int TID = Thread2D::tid();
    int s = TID;
    double sumThread = 0;

    while (s < nbSlice)
	{
	sumThread += f(s * DX);

	s += NB_THREADS;
	}
    tabGM[TID] = sumThread;
    }

/**
 * <pre>
 * Effectue la reduction de tabGM cote device, par ecrasement 2 ? 2 successif.
 * Ce kernel d ecrasement est appeler depuis le host dans une boucle, avec le bon nombre de thread
 *
 * Hypothese : |tabGM| est une puissance de 2
 *
 * Output: le resultat de la reduction est tans tabGM[0]
 * </pre>
 */
__global__ void ecrasementGM(float* tabGM , int middle)
    {
    const int TID = Thread2D::tid();
    tabGM[TID] = tabGM[TID] + tabGM[TID + middle];
    }

/*--------------------------------------*\
 |*        Private            *|
 \*-------------------------------------*/

__device__ float f(float x)
    {
    return 4.0f / (1 + x * x);
    }
