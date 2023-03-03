#include "DomaineProvider.h"
#include "DamierProvider.h"

#include "ImageCustomDomaine.h"

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/**
 * Override
 */
Image_I* DomaineProvider::createImageGL()
    {
    ColorRGB_01 colorTexte = colorTitle();

    return new ImageCustomDomaine(Provider_uchar4_A::createAnimable(), colorTexte);
    }


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
