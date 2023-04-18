#include "RaytracingProviderGM.h"
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
Grid RaytracingProviderGM::grid()
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    dim3 dg(MP, 4, 1);
    dim3 db(CORE_MP, 6, 1);
    Grid grid(dg,db);
    return grid;
    }

/**
 * Override
 */
Animable_I<uchar4>* RaytracingProviderGM::createAnimable(const Grid& grid , bool isVerbose)
    {
    return RaytracingCreator::createGM(grid, isVerbose);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
