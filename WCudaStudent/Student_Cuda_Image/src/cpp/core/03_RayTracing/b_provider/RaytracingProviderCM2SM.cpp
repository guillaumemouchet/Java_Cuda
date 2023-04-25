#include "RaytracingProviderCM2SM.h"
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
Grid RaytracingProviderCM2SM::grid()
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
Animable_I<uchar4>* RaytracingProviderCM2SM::createAnimable(const Grid& grid , bool isVerbose)
    {
    return RaytracingCreator::createCM2SM(grid, isVerbose);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
