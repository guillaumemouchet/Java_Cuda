#include "DamierProvider.h"
#include "Damier.h"

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
Grid DamierProvider::grid()
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    // disons a optimiser
    dim3 dg(MP, 2, 1);
    dim3 db(CORE_MP, 2, 1);
    Grid grid(dg, db);

    return grid;
    }

/**
 * Override
 */
Animable_I<uchar4>* DamierProvider::createAnimable(const Grid& grid , bool isVerbose)
    {
    DomaineMath domaineMath(0, 0, 2 * PI, 2 * PI);

    // Animation;
    float dt = 2 * PI / 2000;
    int n = 2;

    // Dimension
    int w = 16 * 32 * 2;
    int h = 16 * 32;

    return new Damier(grid, w, h, dt, n, domaineMath, isVerbose);
    }

ColorRGB_01 DamierProvider::colorTitle()
    {
    ColorRGB_01 color(255, 255, 255); // white

    return color;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
