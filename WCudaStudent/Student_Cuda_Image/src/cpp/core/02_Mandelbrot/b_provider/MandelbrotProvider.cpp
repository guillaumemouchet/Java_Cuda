#include "MandelbrotProvider.h"
#include "Mandelbrot.h"

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
Grid MandelbrotProvider::grid()
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    // fp64 (float 64 bits)
#ifdef MANDELBROT_DOUBLE
    dim3 dg(MP, 4, 1);
    dim3 db(CORE_MP, 4, 1);

    Grid grid(dg, db);
    return grid;
#endif

    // fp32 (float 32 bits)
#ifdef MANDELBROT_FLOAT
    dim3 dg(MP, 4, 1);
    dim3 db(CORE_MP, 4, 1);

    Grid grid(dg, db);
    return grid;
#endif

    // fp16 (float 16 bits)
#ifdef MANDELBROT_HALF
    dim3 dg(MP, 4, 1);
    dim3 db(CORE_MP, 4, 1);

    Grid grid(dg, db);
    return grid;
#endif

    assert(false);// ne devrait jamais arriver ici
    }

/**
 * Override
 */
Animable_I<uchar4>* MandelbrotProvider::createAnimable(const Grid& grid , bool isVerbose)
    {
    // Animation;
    int nMin = 1000; // 100
    int nMax = 1000; // 100

    // Domaine init
    double x1 = -2.1;
    double y1 = -1.3;
    double x2 = 0.8;
    double y2 = 1.3;
    DomaineMath domaineMath(x1, y1, x2, y2);

    // Dimension
    int w = 16 * 80;
    int h = 16 * 60;

    return new Mandelbrot(grid, w, h, domaineMath, isVerbose, nMin, nMax);
    }



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
