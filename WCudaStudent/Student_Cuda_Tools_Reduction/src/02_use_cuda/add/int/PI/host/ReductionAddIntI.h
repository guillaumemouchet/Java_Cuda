#pragma once

#include "cudas.h"
#include "Grid.h"
#include "RunnableGPU.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class ReductionAddIntI: public RunnableGPU
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	ReductionAddIntI(const Grid& grid , int* ptrSum, bool isVerbose);

	virtual ~ReductionAddIntI();

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/**
	 * override
	 */
	virtual void run();

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs/Outputs
	int* ptrSum;
	dim3 dg;
	dim3 db;

	// Tools
	int* ptrSumGM;
	size_t sizeSM;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
