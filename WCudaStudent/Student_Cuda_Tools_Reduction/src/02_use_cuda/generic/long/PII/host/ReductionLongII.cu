#include "ReductionLongII.h"

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

extern __global__ void KLongProtocoleII(long* ptrSumGM);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

ReductionLongII::ReductionLongII(const Grid& grid , long* ptrSum,bool isVerbose) :
	RunnableGPU(grid, "ReductionLongII-" + to_string(grid.threadCounts()),isVerbose), // classe parente
	ptrSum(ptrSum),
	dg(grid.dg),
	db(grid.db)
    {
    // TODO ReductionLongII
    this->sizeSM = sizeof(long) * grid.threadByBlock();
    GM::mallocLong0(&ptrSumGM);
    }

ReductionLongII::~ReductionLongII()
    {
    GM::free(ptrSumGM);
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void ReductionLongII::run()
    {
    // TODO R
    KLongProtocoleII<<<dg, db, sizeSM>>>(ptrSumGM);
    GM::memcpyDToH_long(ptrSum, ptrSumGM);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
