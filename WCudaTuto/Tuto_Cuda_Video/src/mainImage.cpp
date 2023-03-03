#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "cudas.h"

#include "ImageVideoProvider.h"

#include "Args.h"
#include "Viewer.h"
using namespace gpu;

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

int mainImage(const Args& args)
    {
    cout << "\n[Image] mode" << endl;

    gpu::GLUTImageViewers::init(args.argc, args.argv); //only once

    // ImageOption : (boolean,boolean) : (isSelection ,isAnimation)
    ImageOption zoomable(true);
    ImageOption nozoomable(false);

    Viewer<ImageVideoProvider> imageVideo(nozoomable, 25, 25); // imageOption px py

    // Common
     gpu::GLUTImageViewers::runALL(); // Bloquant, Tant qu'une fenetre est ouverte

    cout << "\n[Image] end" << endl;

    return EXIT_SUCCESS;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

