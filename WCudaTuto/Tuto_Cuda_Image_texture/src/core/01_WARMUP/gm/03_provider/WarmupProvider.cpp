#include "WarmupProvider.h"
#include "Warmup.h"

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

WarmupProvider::WarmupProvider(bool loadOnlyOneImage) :
	Provider_uchar_A(loadOnlyOneImage)
    {
    // rien de plus
    }

WarmupProvider::~WarmupProvider()
    {
    // rien
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

/**
 * Override
 */
Grid WarmupProvider::grid() // dilatation
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    dim3 dg(MP * 2);
    dim3 db(CORE_MP * 8);
    Grid grid(dg, db);

    return grid;
    }

/**
 * Override
 */
Animable_I<uchar>* WarmupProvider::createAnimable(const Grid& grid , bool isVerbose)
    {
     IteratorImageGray_I* ptrIteratorImageGray = Autoroute::getInstance()->iterator();
    //IteratorImageGray_I* ptrIteratorImageGray = Matrix22::getInstance()->iterator();
     //IteratorImageGray_I* ptrIteratorImageGray = NeilPryde::getInstance()->iterator();

     uchar seuil0255=128;

    return new Warmup(grid, ptrIteratorImageGray,seuil0255);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
