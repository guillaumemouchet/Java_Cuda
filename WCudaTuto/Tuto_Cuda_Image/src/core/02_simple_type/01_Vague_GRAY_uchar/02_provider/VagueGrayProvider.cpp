#include "VagueGrayProvider.h"
#include "VagueGray.h"

#include "Hardware.h"

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
Grid VagueGrayProvider::grid()
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    // disons a optimiser
    dim3 dg(MP, 1, 1);
    dim3 db(CORE_MP, 14, 1);
    Grid grid(dg, db);

    return grid;
    }

/**
 * Override
 */
Animable_I<uchar>* VagueGrayProvider::createAnimable(const Grid& grid , bool isVerbose)
    {
    // Animation;
    int dt = 1;

    // Dimension
    int w = 16 * 32 * 2;
    int h = 16 * 32;

    return new VagueGray(grid, w, h, dt, isVerbose);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
