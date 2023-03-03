#include "DamierRGBAFloatProvider.h"
#include "DamierRGBAFloat.h"

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
Grid DamierRGBAFloatProvider::grid()
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    // disons a optimiser
    dim3 dg(MP, 2, 1);
    dim3 db(CORE_MP, 3, 1);
    Grid grid(dg, db);

    return grid;
    }

/**
 * Override
 */
Animable_I<float4>* DamierRGBAFloatProvider::createAnimable(const Grid& grid , bool isVerbose)
    {
    DomaineMath domaineMath(0, 0, 2 * PI, 2 * PI);

    // Animation;
    float dt = 2 * PI / 2000;
    int n = 2;

    // Dimension
    int w = 16 * 32 * 2;
    int h = 16 * 32;

    return new DamierRGBAFloat(grid, w, h, dt, n, domaineMath, isVerbose);
    }

ColorRGB_01 DamierRGBAFloatProvider::colorTitle()
    {
    ColorRGB_01 color(255, 255, 255); // white

    return color;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
