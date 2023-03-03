#include "TutoTextureCuarrayProvider.h"
#include "TutoTextureCuarray.h"

#include "Grid.h"
#include "Hardware.h"

#include "Autoroute.h"
#include "NeilPryde.h"
#include "Matrix22.h"

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur		*|
 \*-------------------------------------*/

TutoTextureCuarrayProvider::TutoTextureCuarrayProvider(bool loadOnlyOneImage) :
Provider_uchar_A(loadOnlyOneImage)
    {
    // rien de plus
    }

TutoTextureCuarrayProvider::~TutoTextureCuarrayProvider()
    {
    // rien
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

/**
 * Override
 */
Grid TutoTextureCuarrayProvider::grid() //dilatation
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    dim3 dg(MP * 4, 1, 1);
    dim3 db(CORE_MP * 9, 1, 1);
    Grid grid(dg, db);

    return grid;
    }

/**
 * Override
 */
Animable_I<uchar>* TutoTextureCuarrayProvider::createAnimable(const Grid& grid , bool isVerbose)
    {
    IteratorImageGray_I* ptrIteratorImageGray = Autoroute::getInstance()->iterator();
     //IteratorImageGray_I* ptrIteratorImageGray = Matrix22::getInstance()->iterator();
     //IteratorImageGray_I* ptrIteratorImageGray = NeilPryde::getInstance()->iterator();

     uchar seuil0255 = 128;

    return new TutoTextureCuarray(grid,ptrIteratorImageGray,seuil0255);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
