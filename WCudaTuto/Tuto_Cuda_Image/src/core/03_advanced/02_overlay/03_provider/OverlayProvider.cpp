#include "OverlayProvider.h"

#include "ImageOverlay.h"

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
Image_I* OverlayProvider::createImageGL()
    {
    ColorRGB_01 colorTexte = colorTitle();

    return new ImageOverlay(Provider_uchar4_A::createAnimable(), colorTexte);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
