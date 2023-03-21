#include "ReductionAddIntI.h"

#include <assert.h>
#include <GM.h>
#include <GM_MemoryManagement.h>
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

extern __global__ void KAddIntProtocoleI(int* ptrSumGM);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

ReductionAddIntI::ReductionAddIntI(const Grid& grid , int* ptrSum , bool isVerbose) :
	RunnableGPU(grid, "ReductionAddIntI-" + to_string(grid.threadCounts()), isVerbose), // classe parente
	ptrSum(ptrSum),
	dg(grid.dg),
	db(grid.db)
    {
    // TODO ReductionAddIntI
    // MM pour ptrSumGM (oubliez pas initialisation)
    this->sizeSM = sizeof(int) * grid.threadByBlock();
    // Tip:  Il y a une methode dedier pour malloquer un int cote device et l'initialiser a zero
    //
    GM::mallocInt0(&ptrSumGM);
    }

ReductionAddIntI::~ReductionAddIntI()
    {
    GM::free(ptrSumGM);
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void ReductionAddIntI::run()
    {
    // TODO ReductionAddIntI
    // appeler le kernel
    // recuperer le resulat coter host
    KAddIntProtocoleI<<<dg, db, sizeSM>>>(ptrSumGM);
    // Tip:  Il y a une methode dedier ramener coter host un int
    //
    GM::memcpyDToH_int(ptrSum, ptrSumGM);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
