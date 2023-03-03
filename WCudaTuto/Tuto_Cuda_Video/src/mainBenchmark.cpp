#include <iostream>
#include <stdlib.h>

#include "ImageVideoProvider.h"

#include "BenchmarkImage.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void imageVideo();

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

int mainBenchmark()
    {
    cout << "\n[Benchmark] mode" << endl;

    // Attention : Un a la fois seulement!

    imageVideo();

    cout << "\n[Benchmark] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void imageVideo()
    {
    const double DURATION_MAX_S = 8;

   bool loadOnlyOneImage=true;
    ImageVideoProvider provider(loadOnlyOneImage);

    BenchmarkImage<uchar4>::run(&provider, DURATION_MAX_S);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

