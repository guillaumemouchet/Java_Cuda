#pragma once

#include "TestCuda.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class TestWarmup: public TestCuda
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	TestWarmup();

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    protected:

	/**
	 * Override
	 */
	void allTests();

    private:

	void testSpecial();

	static long thresholdPerformanceFps();

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:


    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

