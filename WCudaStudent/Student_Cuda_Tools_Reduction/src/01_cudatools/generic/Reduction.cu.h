#pragma once

#include "Lock.cu.h"
#include "Thread2D.cu.h"

/*----------------------------------------------------------------------*\
 |*			prt fonction / reduction			*|
 \*---------------------------------------------------------------------*/

#define BinaryOperator(name) T (*name)(T, T)
#define AtomicOp(name) void (*name)(T*, T)

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

class Reduction
    {
    public:

	/**
	 * Hypothese:
	 *
	 * 	(H1) 	BinaryOperator un operateur binaire sur des element de Type T
	 * 	(H2)	AtomicOp permet de realiser des operations atomics
	 *
	 * Usage example :
	 *
	 * 		Version1:
	 *
	 * 			__device__ int add(int x, int y)		{return x+y;}
	 * 			__device__ void addAtomic(int* ptrX, int y)	{atomicAdd(ptrX,y);}
	 *
	 * 			ReductionGeneric::reduce(add,addAtomic,tabSm,ptrResultGM);
	 *
	 * 		Version2:
	 *
	 * 			__device__ int add(int x, int y){return x+y;}
	 *
	 *			#include "Lock.cu.h"
	 * 			__device__ int volatile mutex = 0;		// variable global
	 * 			__device__ void addAtomic(int* ptrX, int y) 	// 10x plus lent que version1, mais plus flexible
	 * 				{
	 * 				Lock locker(&mutex);
	 * 				locker.lock();
	 * 				(*ptrX)+=y;
	 * 				locker.unlock();
	 * 				}
	 *
	 * 			ReductionGeneric::reduce(add,addAtomic,tabSm,ptrResultGM);
	 */
	template <typename T>
	static __device__ void reduce(BinaryOperator(OP) ,AtomicOp(ATOMIC_OP), T* tabSM, T* ptrResultGM)
	//static __device__ void reduce(T (*OP)(T, T) ,void (*ATOMIC_OP)(T*, T), T* tabSM, T* ptrResultGM) // idem ci-dessus mais sans define
	    {
	    // Meme principe que ReductionAdd

	    // TODO ReductionGeneric
	    // Meme principe que ReductionAdd
	    reductionIntraBlock(OP,tabSM);
	    reductionInterBlock(ATOMIC_OP,tabSM, ptrResultGM);
	    }

    private:

	/*--------------------------------------*\
	|*	reductionIntraBlock		*|
	 \*-------------------------------------*/

	/**
	 * used dans une boucle in reductionIntraBlock
	 */
	template <typename T>
	static __device__ void ecrasement(BinaryOperator(OP),T* tabSM, int middle)
	    {
	    // TODO ReductionGeneric
	    // Meme principe que ReductionAdd
	    // OP est la variable representant l'operateur binaire

	const int TID_LOCAL = Thread2D::tidLocalBlock();

		    if(TID_LOCAL < middle)
			{
			tabSM[TID_LOCAL] = OP(tabSM[TID_LOCAL],tabSM[TID_LOCAL + middle]);
			}
	    }

	/**
	 * Sur place, le resultat est dans tabSM[0]
	 */
	template <typename T>
	static __device__ void reductionIntraBlock(BinaryOperator(OP),T* tabSM)
	    {
	    // TODO ReductionGeneric
	    // Meme principe que ReductionAdd
	    // OP est la variable representant l'operateur binaire
	    int m = Thread2D::nbThreadBlock() >> 1;
	   	    while(m > 0)
	   		{
	   		ecrasement(OP,tabSM, m);
	   		m=m>>1;
	   		__syncthreads();
	   		}
	    }

	/*--------------------------------------*\
	|*	reductionInterblock		*|
	 \*-------------------------------------*/

	template <typename T>
	static __device__ void reductionInterBlock(AtomicOp(ATOMIC_OP), T* tabSM, T* ptrResultGM)
	    {
	    // TODO ReductionGeneric
	    // Meme principe que ReductionAdd
	    // ATOMIC_OP est la variable representant l'operateur binaire atomic
	    const int TID_LOCAL = Thread2D::tidLocalBlock();

	    	    if(TID_LOCAL == 0)
	    		{
	    		ATOMIC_OP(ptrResultGM, tabSM[0]);
	    		}
	    }

    };

/*----------------------------------------------------------------------*\
|*			End	 					*|
 \*---------------------------------------------------------------------*/
