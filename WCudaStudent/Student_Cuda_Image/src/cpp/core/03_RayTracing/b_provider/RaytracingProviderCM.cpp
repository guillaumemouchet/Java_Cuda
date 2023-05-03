#include "RaytracingProviderCM.h"
#include "RaytracingCreator.h"

#include "Hardware.h"

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Override		*|
 \*-------------------------------------*/

/**
 * Override
 */
Grid RaytracingProviderCM::grid()
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    dim3 dg(MP, 1, 1);
    dim3 db(CORE_MP, 6, 1);

    Grid grid(dg, db);
    return grid;
    }

/**
 * Override
 */
Animable_I<uchar4>* RaytracingProviderCM::createAnimable(const Grid& grid , bool isVerbose)
    {
    return RaytracingCreator::createCM(grid, isVerbose);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
