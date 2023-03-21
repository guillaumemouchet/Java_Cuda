#include "ReductionIntI.h"

#include <assert.h>
#include <GM.h>
#include <GM_MemoryManagement.h>
#include <Grid.h>
#include <iostream>

using std::cout;
using std::endl;
using std::to_string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void KIntProtocoleI(int* ptrSumGM);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

ReductionIntI::ReductionIntI(const Grid& grid , int* ptrSum , bool isVerbose) :
	RunnableGPU(grid, "ReductionIntI-" + to_string(grid.threadCounts()), isVerbose), // classe parente
	ptrSum(ptrSum), dg(grid.dg), db(grid.db)
    {
    // TODO ReductionIntI
    this->sizeSM = sizeof(int) * grid.threadByBlock();

    GM::mallocInt0(&ptrSumGM);

    }

ReductionIntI::~ReductionIntI()
    {
    // TODO ReductionIntI
    GM::free(ptrSumGM);

    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void ReductionIntI::run()
    {
    KIntProtocoleI<<<dg, db, sizeSM>>>(ptrSumGM);
    // Tip:  Il y a une methode dedier ramener coter host un int
    //
    GM::memcpyDToH_int(ptrSum, ptrSumGM);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
