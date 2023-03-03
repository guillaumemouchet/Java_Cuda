#include <iostream>
#include <stdlib.h>

#include "Videos.h"

#include "WarmupProvider.h"
#include "TutoTextureGMProvider.h"
#include "TutoTextureCuarrayProvider.h"
#include "TutoSurfaceProvider.h"

#include "BenchmarkImage.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void warmup();
static void tutoTextureGM();
static void tutoTextureCuarray();
static void tutoSurface();

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

int mainBenchmark()
    {
    cout << "\n[Benchmark] mode" << endl;

    Videos::preloadONE();

    // Attention : Un a la fois seulement!

    warmup();
    tutoTextureGM();
    tutoTextureCuarray();
    tutoSurface();

    cout << "\n[Benchmark] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void warmup()
    {
    const double DURATION_MAX_S = 8;

    bool loadOnlyOneImage = true;
    WarmupProvider provider(loadOnlyOneImage);

    BenchmarkImage<uchar>::run(&provider, DURATION_MAX_S);
    }

void tutoTextureGM()
    {
    const double DURATION_MAX_S = 8;

    bool loadOnlyOneImage = true;
    TutoTextureGMProvider provider(loadOnlyOneImage);

    BenchmarkImage<uchar>::run(&provider, DURATION_MAX_S);
    }

void tutoTextureCuarray()
    {
    const double DURATION_MAX_S = 8;

    bool loadOnlyOneImage = true;
    TutoTextureCuarrayProvider provider(loadOnlyOneImage);

    BenchmarkImage<uchar>::run(&provider, DURATION_MAX_S);
    }

void tutoSurface()
    {
    const double DURATION_MAX_S = 8;

    bool loadOnlyOneImage = true;
    TutoSurfaceProvider provider(loadOnlyOneImage);

    BenchmarkImage<uchar>::run(&provider, DURATION_MAX_S);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

