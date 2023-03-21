#pragma once

#include <RunnableGPU.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class ReductionIntI: public RunnableGPU
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	ReductionIntI(const Grid& grid , int* ptrSum , bool isVerbose);

	virtual ~ReductionIntI();

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
