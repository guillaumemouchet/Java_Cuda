#include <assert.h>

#include "Thread2D.cu.h"
#include "cudas.h"
#include "Indices.cu.h"

#include "Sphere.h"
#include "nbSphere.h"
#include "GM.h"


#include "raytracingCM.cu.h"
#include "RaytracingMath.cu.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static __device__ void work(uchar4* tabPixelsGM, uint w, uint h, float t, Sphere* tabSpheresDev, int nbSpheres);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

__global__ void kernelRaytacingGM(uchar4* tabPixelsGM , uint w , uint h , float t , Sphere* tabSpheresGM , int nbSpheres)
    {
    // TODO Raytracing GPU GM

    // Indications :
    //		(I1) Call methode work with good input
    // 		(I2) work contain the algo
    //		(I3) The algo is the same with the GM,CM,SM of TP Ractracing
    work(tabPixelsGM,w,h,t,tabSpheresGM, nbSpheres);
    }

__global__ void kernelRaytacingSM(uchar4* tabPixelsGM , uint w , uint h , float t , Sphere* tabSpheresGM , int nbSpheres)
    {
    // TODO Raytracing GPU SM
    extern __shared__ Sphere tabSM[];

    const int NB_THREADS = Thread2D::nbThreadLocal();
    const int TID_LOCAL = Thread2D::tidLocalBlock();

    int s = TID_LOCAL;

    while (s < nbSpheres)
       {
	tabSM[s] = tabSpheresGM[s];

   	s += NB_THREADS;
       }
    __syncthreads();

    work(tabPixelsGM,w,h,t,tabSM, nbSpheres);

    // Indications :
    //		(I1) Copier les sphere de GM to SM
    // 		(I2) Call work with good input
    //		(I3) Implementer une methode copyGMtoSM
    }

__global__ void kernelRaytacingCM(uchar4* tabPixelsGM , uint w , uint h , float t , int nbSpheres)
    {
    // TODO Raytracing GPU CM

    // Indications :
    //		(I1) call work with good input
    // 		(I2) TAB_SPHERES_CM est une variable globale a ce fichier! (Voir le debut de ce fichier, include rayTracingCM.h)
    work(tabPixelsGM,w,h,t,TAB_SPHERES_CM, nbSpheres);
    }

__global__ void kernelRaytacingCM2SM(uchar4* tabPixelsGM , uint w , uint h , float t , int nbSpheres)
    {
    // TODO Raytracing GPU SM_BY_CM
    extern __shared__ Sphere tabSM[];

    const int NB_THREADS = Thread2D::nbThreadLocal();
    const int TID_LOCAL = Thread2D::tidLocalBlock();

    int s = TID_LOCAL;

    while (s < nbSpheres)
       {
	tabSM[s] = TAB_SPHERES_CM[s];

	s += NB_THREADS;
       }
    __syncthreads();

    work(tabPixelsGM,w,h,t,tabSM, nbSpheres);

    // Indications :
    //		(I1) Copier les sphere de CM to SM
    // 		(I2) Call work with good input
    //		(I3) Implementer une methode copyCMtoSM
    //		     ou : Tip : renommer copyGMtoSM en copyDevToSM et utiliser copyDevToSM avec les bons inputs
    }

/*--------------------------------------*\
 |*		private			*|
 \*-------------------------------------*/

/**
 * Methode commune au 3 kernel ci-dessus.
 * Ici on ne sait pas si derriere tabSpheresDev, c'est
 * 	- de la GM?
 * 	- de la SM?
 * 	- de la CM?
 * Pas d'importance, c'est un pointeur et on travail avec!
 */
__device__ void work(uchar4* tabPixelsGM , uint w , uint h , float t , Sphere* tabSpheresDev , int nbSpheres)
    {
    // TODO Raytracing work device side
    // create RaytracingMath
    RaytracingMath raytracingMath(tabSpheresDev, nbSpheres, t);
    // entrelacement
    const int TID = Thread2D::tid();
    const int NB_THREAD = Thread2D::nbThread();
    const int WH = w * h;

    int s = TID;
    int i = 0;
    int j = 0;
    while(s< WH)
	{
	Indices::toIJ(s,w,&i,&j);
	raytracingMath.colorIJ(&tabPixelsGM[s],i, j);
	s+=NB_THREAD;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

