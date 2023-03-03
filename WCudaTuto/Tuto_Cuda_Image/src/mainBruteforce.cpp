#include <iostream>
#include <stdlib.h>

#include "VagueProvider.h"
#include "DamierProvider.h"
#include "VagueGrayProvider.h"
#include "DamierRGBAFloatProvider.h"
#include "DamierHSBAFloatProvider.h"
#include "DamierHueFloatProvider.h"

#include "Iterator.h"
#include "BruteForce.h"
#include "Hardware.h"

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |* Declaration *|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void vague(Matlab* ptrMatlab);
static void damier(Matlab* ptrMatlab);
static void vagueGray(Matlab* ptrMatlab);
static void damierRGBAfloat(Matlab* ptrMatlab);
static void damierHSBAfloat(Matlab* ptrMatlab);
static void damierHUEfloat(Matlab* ptrMatlab);

//tools
template<typename T>
static void bruteForce(ProviderUse_I* ptrProviderUse , Matlab* ptrMatlab , const PlotType& plotType , double durationMaxS = 0.5);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainBrutforce()
    {
    cout << "\n[BruteForce] mode" << endl;

    Matlab matlab;

    // Attention : Un a la fois seulement!

    vague(&matlab);
    vagueGray(&matlab);

    damier(&matlab);
    damierRGBAfloat(&matlab);
    damierHSBAfloat(&matlab);
    damierHUEfloat(&matlab);

    matlab.play();

    cout << "\n[BruteForce] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void vague(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.5; // 1 grid
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    VagueProvider provider;
    bruteForce<uchar4>((ProviderUse_I*)&provider, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }

void damier(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.5; // 1 grid
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    DamierProvider provider;
    bruteForce<uchar4>((ProviderUse_I*)&provider, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }

void vagueGray(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.5; // 1 grid
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    VagueGrayProvider provider;
    bruteForce<uchar>((ProviderUse_I*)&provider, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }

void damierRGBAfloat(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.5; // 1 grid
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    DamierRGBAFloatProvider provider;
    bruteForce<float4>((ProviderUse_I*)&provider, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }

void damierHSBAfloat(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.5; // 1 grid
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    DamierHSBAFloatProvider provider;
    bruteForce<float4>((ProviderUse_I*)&provider, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }

void damierHUEfloat(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.5; // 1 grid
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    DamierHueFloatProvider provider;
    bruteForce<float>((ProviderUse_I*)&provider, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
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
