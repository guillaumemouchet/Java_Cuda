#include "EventProvider.h"

#include "VagueProvider.h"

#include "ImageCustomEvent.h"

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
Image_I* EventProvider::createImageGL()
    {
    ColorRGB_01 colorTexte = colorTitle();

    return new ImageCustomEvent(Provider_uchar4_A::createAnimable(), colorTexte);
    }

ColorRGB_01 EventProvider::colorTitle()
    {
    ColorRGB_01 colorTexte(0, 1, 0); // Green

    return colorTexte;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
