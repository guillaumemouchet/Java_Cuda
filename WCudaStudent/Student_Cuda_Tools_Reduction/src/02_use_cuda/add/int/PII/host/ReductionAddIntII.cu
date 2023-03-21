#include "ReductionAddIntII.h"

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

extern __global__ void KAddIntProtocoleII(int* ptrSumGM);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

ReductionAddIntII::ReductionAddIntII(const Grid& grid , int* ptrSum,bool isVerbose) :
	RunnableGPU(grid, "ReductionAddIntII-" + to_string(grid.threadCounts()),isVerbose), // classe parente
	ptrSum(ptrSum),
	dg(grid.dg),
	db(grid.db)
    {
    // TODO ReductionAddIntII
    this->sizeSM = sizeof(int) * grid.threadByBlock();
    GM::mallocInt0(&ptrSumGM);

    }

ReductionAddIntII::~ReductionAddIntII()
    {
    GM::free(ptrSumGM);
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void ReductionAddIntII::run()
    {
    KAddIntProtocoleII<<<dg, db, sizeSM>>>(ptrSumGM);
    GM::memcpyDToH_int(ptrSum, ptrSumGM);

    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
