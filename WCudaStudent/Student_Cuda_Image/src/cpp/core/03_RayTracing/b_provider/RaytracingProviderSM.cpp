#include "RaytracingProviderSM.h"
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
Grid RaytracingProviderSM::grid()
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    // TODO Raytracing
    dim3 dg(MP, 4, 1);
    dim3 db(CORE_MP, 4, 1);

    Grid grid(dg, db);
    return grid;
    }

/**
 * Override
 */
Animable_I<uchar4>* RaytracingProviderSM::createAnimable(const Grid& grid , bool isVerbose)
    {
    return RaytracingCreator::createSM(grid, isVerbose);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
