#include <iostream>
#include <stdlib.h>

#include "Iterator.h"
#include "BruteForce.h"
#include "Hardware.h"

#include "Videos.h"

#include "WarmupProvider.h"
#include "TutoTextureGMProvider.h"
#include "TutoTextureCuarrayProvider.h"
#include "TutoSurfaceProvider.h"

using std::cerr;
using std::cout;
using std::endl;
using std::to_string;

/*----------------------------------------------------------------------*\
 |* Declaration *|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void warmup(Matlab* ptrMatlab);
static void tutoTextureGM(Matlab* ptrMatlab);
static void tutoTextureCuarray(Matlab* ptrMatlab);
static void tutoSurface(Matlab* ptrMatlab);

//tools
template<typename T>
static void bruteForce(ProviderUse_I* ptrProviderUse , Matlab* ptrMatlab , const PlotType& plotType , double durationMaxS = 0.5);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

int mainBrutforce()
    {
    cout << "\n[BruteForce] mode" << endl;

    Videos::preloadONE();

    Matlab matlab;

    // Attention : Un a la fois seulement!

    warmup(&matlab);
    tutoTextureGM(&matlab);
    tutoTextureCuarray(&matlab);
    tutoSurface(&matlab);

    matlab.play();

    cout << "\n[BruteForce] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void warmup(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.5; // 1 grid
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    bool loadOnlyOneImage = true;
    WarmupProvider provider(loadOnlyOneImage);
    bruteForce<uchar4>((ProviderUse_I*)&provider, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }

void tutoTextureGM(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.5; // 1 grid
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    bool loadOnlyOneImage = true;
    TutoTextureGMProvider provider(loadOnlyOneImage);
    bruteForce<uchar4>((ProviderUse_I*)&provider, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }

void tutoTextureCuarray(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.5; // 1 grid
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    bool loadOnlyOneImage = true;
    TutoTextureCuarrayProvider provider(loadOnlyOneImage);
    bruteForce<uchar4>((ProviderUse_I*)&provider, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }

void tutoSurface(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.5; // 1 grid
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    bool loadOnlyOneImage = true;
    TutoSurfaceProvider provider(loadOnlyOneImage);
    bruteForce<uchar4>((ProviderUse_I*)&provider, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }


/*--------------------------------------*\
 |*		Tools			*|
 \*-------------------------------------*/

template<typename T>
void bruteForce(ProviderUse_I* ptrProviderUse , Matlab* ptrMatlab , const PlotType& plotType , double durationMaxS)
    {
// Hardware
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();
    const int NB_THREAD_BLOCK_MAX = Hardware::getMaxThreadPerBlock();
    const int WARP_SIZE = Hardware::getWarpSize();

// dg
    Iterator iteratorDGx(MP, 10 * MP, MP, Operator::ADD); // (min,max,step)

// db
    Iterator iteratorDBx(CORE_MP, NB_THREAD_BLOCK_MAX, CORE_MP, Operator::ADD);
// Iterator iteratorDBx(CORE_MP, NB_THREAD_BLOCK_MAX, WARP_SIZE, Operator::ADD);
// Iterator iteratorDBx(CORE_MP, NB_THREAD_BLOCK_MAX, 2, Operator::MULTIPLY); // power2 (reduction)

// gridMaillage
    GridMaillage gridMaillage(iteratorDGx, iteratorDBx);

    BruteForce::run(ptrProviderUse, &gridMaillage, ptrMatlab, plotType, durationMaxS);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
