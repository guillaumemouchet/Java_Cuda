#include "ReductionIntII.h"

#include "GM.h"
#include "Grid.h"

#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;
using std::to_string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void KIntProtocoleII(int* ptrSumGM);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

ReductionIntII::ReductionIntII(const Grid& grid , int* ptrSum,bool isVerbose) :
	RunnableGPU(grid, "ReductionIntII-" + to_string(grid.threadCounts()),isVerbose), // classe parente
	ptrSum(ptrSum),
	dg(grid.dg),
	db(grid.db)
    {
    // TODO ReductionIntII
    this->sizeSM = sizeof(int) * grid.threadByBlock();
        GM::mallocInt0(&ptrSumGM);    }

ReductionIntII::~ReductionIntII()
    {
    GM::free(ptrSumGM);
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void ReductionIntII::run()
    {
    KIntProtocoleII<<<dg, db, sizeSM>>>(ptrSumGM);
    GM::memcpyDToH_int(ptrSum, ptrSumGM);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
