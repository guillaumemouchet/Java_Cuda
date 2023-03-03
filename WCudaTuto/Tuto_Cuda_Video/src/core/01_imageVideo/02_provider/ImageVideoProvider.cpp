#include "ImageVideo.h"
#include "ImageVideoProvider.h"

#include "Grid.h"
#include "Hardware.h"

#include "VideoShop.h"

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur		*|
 \*-------------------------------------*/

ImageVideoProvider::ImageVideoProvider(bool loadOnlyOneImage) :
	loadOnlyOneImage(loadOnlyOneImage)
    {
    // rien de plus
    }

ImageVideoProvider::~ImageVideoProvider()
    {
    // rien
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

/**
 * Override
 */
Grid ImageVideoProvider::grid()
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    dim3 dg(MP * 9, 1, 1);
    dim3 db(CORE_MP * 7, 1, 1); // grid 1d
    Grid grid(dg, db);

    return grid;
    }

/**
 * Override
 */
Animable_I<uchar4>* ImageVideoProvider::createAnimable(const Grid& grid , bool isVerbose)
    {
    int w;
    int h;
    int nbImageToLoad;
    string fileVideo = VideoShop::autoroute(&w, &h, &nbImageToLoad);
    // string fileVideo = VideoShop::neilpryde(&w, &h,&nbImageToLoad);

    if (loadOnlyOneImage)
	{
	nbImageToLoad = 1; // pour bruteForce (Pas charger la video complete a chaque fois, idem benchmarking)
	}

    return new ImageVideo(grid, w, h, fileVideo, nbImageToLoad);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
