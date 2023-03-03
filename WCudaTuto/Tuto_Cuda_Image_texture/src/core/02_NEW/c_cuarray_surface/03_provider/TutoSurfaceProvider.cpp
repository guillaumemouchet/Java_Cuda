#include "TutoSurfaceProvider.h"
#include "TutoSurface.h"

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

TutoSurfaceProvider::TutoSurfaceProvider(bool loadOnlyOneImage) :
	Provider_uchar_A(loadOnlyOneImage)
    {
    // rien de plus
    }

TutoSurfaceProvider::~TutoSurfaceProvider()
    {
    // rien
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

/**
 * Override
 */
Grid TutoSurfaceProvider::grid() //dilatation
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    dim3 dg(MP * 1, 1, 1);
    dim3 db(CORE_MP*8, 1, 1);
    Grid grid(dg, db);

    return grid;
    }

/**
 * Override
 */
Animable_I<uchar>* TutoSurfaceProvider::createAnimable(const Grid& grid , bool isVerbose)
    {
    IteratorImageGray_I* ptrIteratorImageGray = Autoroute::getInstance()->iterator();
     //IteratorImageGray_I* ptrIteratorImageGray = Matrix22::getInstance()->iterator();
     //IteratorImageGray_I* ptrIteratorImageGray = NeilPryde::getInstance()->iterator();

     uchar seuil0255 = 128;

    return new TutoSurface(grid,ptrIteratorImageGray,seuil0255);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
