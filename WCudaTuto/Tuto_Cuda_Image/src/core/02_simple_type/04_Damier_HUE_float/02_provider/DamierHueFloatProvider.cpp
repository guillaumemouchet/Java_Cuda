#include "DamierHueFloatProvider.h"
#include "DamierHueFloat.h"

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
Grid DamierHueFloatProvider::grid()
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    // A optimiser
    dim3 dg(MP, 2, 1);
    dim3 db(CORE_MP, 4, 1);
    Grid grid(dg, db);

    return grid;
    }

/**
 * Override
 */
Animable_I<float>* DamierHueFloatProvider::createAnimable(const Grid& grid , bool isVerbose)
    {
    DomaineMath domaineMath(0, 0, 2 * PI, 2 * PI);

    // Animation;
    float dt = 2 * PI / 2000;
    int n = 2;

    // Dimension
    int w = 16 * 32 * 2;
    int h = 16 * 32;

    return new DamierHueFloat(grid, w, h, dt, n, domaineMath, isVerbose);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
