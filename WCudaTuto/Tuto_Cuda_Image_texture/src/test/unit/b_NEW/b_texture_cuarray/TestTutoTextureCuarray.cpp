#include "TestTutoTextureCuarray.h"
#include "TutoTextureCuarrayProvider.h"

#include <iostream>
#include <assert.h>

using std::cerr;
using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructor		*|
 \*-------------------------------------*/

TestTutoTextureCuarray::TestTutoTextureCuarray() :
	TestCuda((ProviderUse_I*)new TutoTextureCuarrayProvider())
    {
    enableTestPerformance(true, thresholdPerformanceFps());
    }

/*--------------------------------------*\
 |*		Methodes		*|
 \*-------------------------------------*/

/**
 * Override
 */
void TestTutoTextureCuarray::allTests()
    {
    TEST_ADD(TestCuda::testPerformance); // @suppress("Invalid overload")
    TEST_ADD(TestTutoTextureCuarray::testSpecial);
    }

/**
 * si on le met pas probleme de title dans le html (workaround for this, le test en soi n'est pas important
 */
void TestTutoTextureCuarray::testSpecial()
    {
    showTitle("Test special ");

    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    const bool IS_CHECK_HEURISTIC = false;
    dim3 dg(64, 1, 1);
    dim3 db(1024, 1, 1);
    Grid grid(dg, db, IS_CHECK_HEURISTIC); // power 2

    test(grid);
    }

/*--------------------------------------*\
 |*		private			*|
 \*-------------------------------------*/

/**
 * static
 */
long TestTutoTextureCuarray::thresholdPerformanceFps()
    {
    return 3800; // cbi naif  4300
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

