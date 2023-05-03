#include "AddVectorTristream.h"

#include <assert.h>
#include <GM.h>
#include <GM_MemoryManagement.h>
#include <Stream.h>
#include <iostream>

#include "../../00_tools/VectorTools.h"

using std::cout;
using std::endl;
using std::to_string;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void addVector(int* ptrDevV1 , int* ptrDevV2 , int* ptrDevW , int n,int sliceIndex=0);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

AddVectorTristream::AddVectorTristream(const Grid& grid , int* ptrV1 , int* ptrV2 , int* ptrW , int n , int nbSlice , bool isVerbose) :
	RunnableGPU(grid, title(nbSlice) + "-" + to_string(n), isVerbose), // classe parente
	//
	ptrV1(ptrV1), //
	ptrV2(ptrV2), //
	ptrW(ptrW), //
	n(n), //
	nbSlice(nbSlice)
    {
    assert(n % nbSlice == 0); // on suppose que chaque slice a la meme taille
    assert(nbSlice >= 3);

    this->sizeVector = n * sizeof(int); // octet
    this->SIZE_SLICE = sizeVector / nbSlice; // TODO addVector en octet
    this->N_BY_SLICE = n / nbSlice; // TODO addVector nb case by slice

    // MM (malloc Device)
	{
	GM::malloc0(&ptrDevV1, sizeVector);
	GM::malloc0(&ptrDevV2, sizeVector);
	GM::malloc0(&ptrDevW, sizeVector);
	}

    // Stream
	{
	// TODO addVector, see attribute in .h
	Stream::create(&stream0);
	Stream::create(&stream1);
	Stream::create(&stream2);
	}
    }

AddVectorTristream::~AddVectorTristream(void)
    {
    //MM (device free)
	{
	GM::free(ptrDevV1);
	GM::free(ptrDevV2);
	GM::free(ptrDevW);
	}

    // Stream
	{
	// TODO addVector, see attribute in .h
	Stream::destroy(stream0);
	Stream::destroy(stream1);
	Stream::destroy(stream2);
	}
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

/**
 * Conseils :
 *
 * 	(C1) Commencer par les warmup pour un nombre de slice petit et fixe, puis passer seulement ensuite a la generalisation.
 * 	(C2) Pour les warmup, prenez une taille n de vecteur petit (pour pouvoir afficher le resultat)
 * 	     Aller dans VectorTools::n(); // activez la ligne debug provisoirement, et dans nDebug() prenez une valeur peitite et divisible par votre nombre se slice
 * 	(C3) Travailler au début avec mainUse.cpp (utiliser le blog debug fournit avec flag de verbosite a false avec !)
 */
void AddVectorTristream::run()
    {
    // Warmup
	{
	//run3Slice();
	//run4Slice();
	//run5Slice();
	}

    runGeneric();
    // Synchronize
	{
	Stream::synchronize(stream0);
	Stream::synchronize(stream1);
	Stream::synchronize(stream2);

	}
    }

/**
 * Warmup : 3 slice
 */
void AddVectorTristream::run3Slice()
    {
    // Warning : use private methode:
    //			- void copyHtoD(int sliceIndex , cudaStream_t stream)
    //			- void copyDtoH(int sliceIndex , cudaStream_t stream)
    //			- kernelSlice(int sliceIndex , cudaStream_t stream)
    // voir en bas de fichier

    // step1 :
	{
	copyHtoD(0, stream0);
	}

    // step2 :
	{
	copyHtoD(1, stream1);
	kernelSlice(0, stream0);

	}

// partie centrale 3 stream en parallel

    // step3 : (1 seul step pour 3 slice et 3 stream)
	{
	copyHtoD(2, stream2);
	kernelSlice(1, stream1);
	copyDtoH(0, stream0);

	}

    // step 4 :
	{
	kernelSlice(2, stream2);
	copyDtoH(1, stream1);

	}

// step 5 :
	{
	copyDtoH(2, stream2);
	}
    }

/**
 * Warmup : 4 slice
 */
void AddVectorTristream::run4Slice()
    {

// Warning : use private methode:
//			- void copyHtoD(int sliceIndex , cudaStream_t stream)
//			- void copyDtoH(int sliceIndex , cudaStream_t stream)
//			- kernelSlice(int sliceIndex , cudaStream_t stream)

// partie Init
	{
	// step1
	    {
	    copyHtoD(0, stream0);
	    }

	// step2
	    {
	    copyHtoD(1, stream1);
	    kernelSlice(0, stream0);
	    }
	}

// partie centrale 3 stream en parallel
	{
	// step3
	    {
	    copyHtoD(2, stream2);
	    kernelSlice(1, stream1);
	    copyDtoH(0, stream0);
	    }

	// step4
	    {
	    copyHtoD(3, stream0);
	    kernelSlice(2, stream2);
	    copyDtoH(1, stream1);
	    }
	}

// partie Finale
	{
	// step 4
	    {
	    kernelSlice(3, stream0);
	    copyDtoH(2, stream2);
	    }

	//step 5
	    {
	    copyDtoH(3, stream0);

	    }
	}
    }

/**
 * Warmup : 5 slice
 */
void AddVectorTristream::run5Slice()
    {
// Warning : use private methode:
//			- void copyHtoD(int sliceIndex , cudaStream_t stream)
//			- void copyDtoH(int sliceIndex , cudaStream_t stream)
//			- kernelSlice(int sliceIndex , cudaStream_t stream)

// partie Init
	{
	// step1
	    {
	    copyHtoD(0, stream0);

	    }

	// step2
	    {
	    copyHtoD(1, stream1);
	    kernelSlice(0, stream0);
	    }
	}

// partie centrale 3 stream en parallel
	{
	// step3
	    {
	    copyHtoD(2, stream2);
	    kernelSlice(1, stream1);
	    copyDtoH(0, stream0);
	    }

	// step4
	    {
	    copyHtoD(3, stream0);
	    kernelSlice(2, stream2);
	    copyDtoH(1, stream1);
	    }

	// step 5
	    {
	    copyHtoD(4, stream1);
	    kernelSlice(3, stream0);
	    copyDtoH(2, stream2);
	    }
	}

// partie finale
	{
	const int INDEX_LAST = -1;        // TODO 		// un peu de genericiter
	const int INDEX_BEFORE_LAST = INDEX_LAST - 1; 	// un peu de genericiter

	// before last
	    {
	    kernelSlice(INDEX_LAST, stream1);
	    copyDtoH(INDEX_BEFORE_LAST, stream0);
	    }

	// last
	    {
	    copyDtoH(INDEX_LAST, stream1);

	    }
	}
    }

void AddVectorTristream::runGeneric()
    {
// Warning : use private methode:
//			- void copyHtoD(int sliceIndex , cudaStream_t stream)
//			- void copyDtoH(int sliceIndex , cudaStream_t stream)
//			- kernelSlice(int sliceIndex , cudaStream_t stream)

// partie Init
	{
	// step1
	    {
	    copyHtoD(0, stream0);
	    }

	// step2
	    {
	    copyHtoD(1, stream1);
	    kernelSlice(0, stream0);
	    }
	}

// 6 variable utile pour les permutations
    cudaStream_t streamA = stream0; // cudaStream_t est un int
    cudaStream_t streamB = stream2;
    cudaStream_t streamC = stream1;

    cudaStream_t streamA_old = stream0;
    cudaStream_t streamB_old = stream2;
    cudaStream_t streamC_old = stream1;

// partie centrale 3 stream en parallel
	{
	for (int i = 2; i < nbSlice; i++)
	    {
	    copyHtoD(i, streamB);
	    kernelSlice(i - 1, streamC);
	    copyDtoH(i - 2, streamA);
	    /*
	     *  copyHtoD(2, stream2); ==B
	     *	kernelSlice(1, stream1); ==C
	     *	copyDtoH(0, stream0); ==A
	     */
	    // Reset old stream
	    streamA_old = streamA;
	    streamB_old = streamB;
	    streamC_old = streamC;

	    //set streams to new values in a circular way A->C->B->A
	    streamA = streamC_old;
	    streamB = streamA_old;
	    streamC = streamB_old;

	    }
	}

// partie finale
	{
	const int INDEX_LAST = nbSlice - 1;
	const int INDEX_BEFORE_LAST = INDEX_LAST - 1;

	// before last
	    {
	    kernelSlice(INDEX_LAST, streamB_old);
	    copyDtoH(INDEX_BEFORE_LAST, streamC_old);
	    }

	// last
	    {
	    copyDtoH(INDEX_LAST, streamB_old);

	    }
	}
    }

/**
 * override
 */
double AddVectorTristream::getInputGO()
    {
    return ((long)2 * (long)n * (long)sizeof(half)) / (double)((long)1024 * (long)1024 * (long)1024);
    }

/**
 * override
 */
double AddVectorTristream::getOutputGO()
    {
    return ((long)1 * (long)n * (long)sizeof(half)) / (double)((long)1024 * (long)1024 * (long)1024);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * copyHtoD: la slice sliceIndex pour
 * 	v1
 * 	v2
 * ou
 * 	sliceIndex in [0,nbSlice[
 */
void AddVectorTristream::copyHtoD(int sliceIndex , cudaStream_t stream)
    {
    const int OFFSET_SLICE = sliceIndex * N_BY_SLICE;

// addVector
// Copier sur le device la slice de v1 correspondand a sliceIndex  sur la stream demander
// idem pour v2
    GM::memcpyAsyncHToD(ptrDevV1 + OFFSET_SLICE, ptrV1 + OFFSET_SLICE, SIZE_SLICE, stream);
    GM::memcpyAsyncHToD(ptrDevV2 + OFFSET_SLICE, ptrV2 + OFFSET_SLICE, SIZE_SLICE, stream);
    }

/**
 * copyDtoH: la slice sliceIndex pour
 * 	w
 * ou
 * 	sliceIndex in [0,nbSlice[
 */
void AddVectorTristream::copyDtoH(int sliceIndex , cudaStream_t stream)
    {
    const int OFFSET_SLICE = sliceIndex * N_BY_SLICE;

// addVector
// Copier sur le host la slice de w correspondand à sliceIndex  sur la stream demander
    GM::memcpyAsyncDToH(ptrW + OFFSET_SLICE, ptrDevW + OFFSET_SLICE, SIZE_SLICE, stream);
    }

/**
 * lance le kernel de calcul pour la slice sliceIndex
 * ou
 * 	sliceIndex in [0,nbSlice[
 */
void AddVectorTristream::kernelSlice(int sliceIndex , cudaStream_t stream)
    {
    const int OFFSET_SLICE = sliceIndex * N_BY_SLICE;

// addVector
// appeler le kernel sur la slice correspondant a sliceIndex
    addVector<<<dg,db,0,stream>>>(ptrDevV1 + OFFSET_SLICE, ptrDevV2 + OFFSET_SLICE, ptrDevW + OFFSET_SLICE, N_BY_SLICE, sliceIndex);
}

string AddVectorTristream::title(int nbSlice)
{
    if (VectorTools::isDMA())
	{
	return "Addvector-tristream-slice" + to_string(nbSlice) + "-DMA-int";
	}
    else
	{
	return "Addvector-tristream-slice" + to_string(nbSlice) + "-DMA-int";
	}
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
