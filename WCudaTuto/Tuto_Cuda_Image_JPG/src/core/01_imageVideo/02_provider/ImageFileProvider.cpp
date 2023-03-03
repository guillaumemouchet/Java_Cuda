#include "ImageFile.h"
#include "ImageFileProvider.h"

#include "Grid.h"
#include "Hardware.h"
#include "Image.h"

#include "VideoShop.h"

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur		*|
 \*-------------------------------------*/

ImageFileProvider::ImageFileProvider()
    {
    // rien de plus
    }

ImageFileProvider::~ImageFileProvider()
    {
    // rien
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

/**
 * Override
 */
Grid ImageFileProvider::grid()
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
Animable_I<uchar4>* ImageFileProvider::createAnimable(const Grid& grid , bool isVerbose)
    {
    const string PATH = "/opt/cbi/data/image/";

    string name = "niviuk_3200_2133.jpeg";
    // string name = "maze_1258_1251.jpg";
    // string name = "alpha7_2048_1050.jpg";
    // string name = "champ_1600_1200.jpg";
    // string name = "aonic_500_318.jpg";

    string fileName = PATH + name;
    Image image(fileName);

    return new ImageFile(grid, image);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
