#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "cudas.h"
#include "Args.h"
#include "Viewer.h"
#include "Videos.h"

#include "WarmupProvider.h"
#include "TutoTextureGMProvider.h"
#include "TutoTextureCuarrayProvider.h"
#include "TutoSurfaceProvider.h"

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

    // Videos::preloadONE();
    Videos::preloadALL();

    // ImageOption : (boolean,boolean) : (isSelection ,isAnimation)
    ImageOption zoomable(true);
    ImageOption nozoomable(false);

    Viewer<WarmupProvider> warmup(nozoomable, 0, 0); // imageOption px py
    Viewer<TutoTextureGMProvider> tutoTextureGM(nozoomable, 25, 25);
    Viewer<TutoTextureCuarrayProvider> tutoTextureCuarray(nozoomable, 50, 50);
    Viewer<TutoSurfaceProvider> tutoSurface(nozoomable, 75, 75);

    // Common
    gpu::GLUTImageViewers::runALL(); // Bloquant, Tant qu'une fenetre est ouverte

    cout << "\n[Image] end" << endl;

    return EXIT_SUCCESS;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

