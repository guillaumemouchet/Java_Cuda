#include <iostream>
#include <stdlib.h>

#include "ImageFileProvider.h"

#include "BenchmarkImage.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void imageFile();

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

int mainBenchmark()
    {
    cout << "\n[Benchmark] mode" << endl;

    // Attention : Un a la fois seulement!

    imageFile();

    cout << "\n[Benchmark] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void imageFile()
    {
    const double DURATION_MAX_S = 8;

    ImageFileProvider provider;

    BenchmarkImage<uchar4>::run(&provider, DURATION_MAX_S);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

