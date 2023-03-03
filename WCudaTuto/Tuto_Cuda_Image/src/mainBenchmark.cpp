#include <iostream>
#include <stdlib.h>

#include "VagueProvider.h"
#include "DamierProvider.h"
#include "VagueGrayProvider.h"
#include "DamierRGBAFloatProvider.h"
#include "DamierHSBAFloatProvider.h"
#include "DamierHueFloatProvider.h"

#include "BenchmarkImage.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void vague();
static void damier();
static void vagueGray();
static void damierRGBAFloat();
static void damierHSBAFloat();
static void damierHueFloat();

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainBenchmark()
    {
    cout << "\n[Benchmark] mode" << endl;

    // Attention : Un a la fois seulement!

    vague();
    vagueGray();

    damier();
    damierRGBAFloat();
    damierHSBAFloat();
    damierHueFloat();

    cout << "\n[Benchmark] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void vague()
    {
    const double DURATION_MAX_S = 8;

    VagueProvider provider;
    BenchmarkImage<uchar4>::run(&provider, DURATION_MAX_S);
    }

void damier()
    {
    const double DURATION_MAX_S = 8;

    DamierProvider provider;
    BenchmarkImage<uchar4>::run(&provider, DURATION_MAX_S);
    }

void vagueGray()
    {
    const double DURATION_MAX_S = 8;

    VagueGrayProvider provider;
    BenchmarkImage<uchar>::run(&provider, DURATION_MAX_S);
    }

void damierRGBAFloat()
    {
    const double DURATION_MAX_S = 8;

    DamierRGBAFloatProvider provider;
    BenchmarkImage<float4>::run(&provider, DURATION_MAX_S);
    }

void damierHSBAFloat()
    {
    const double DURATION_MAX_S = 8;

    DamierHSBAFloatProvider provider;
    BenchmarkImage<float4>::run(&provider, DURATION_MAX_S);

    // Attention (interpretation result):
    // Ici shader ne travaille plus,
    // donc par rapport a une version rgba sans shader,
    // le travaille a faire ici est plus petit
    }

void damierHueFloat()
    {
    const double DURATION_MAX_S = 8;

    DamierHueFloatProvider provider;
    BenchmarkImage<float>::run(&provider, DURATION_MAX_S);

    // Attention (interpretation result):
    // Ici shader ne travaille plus,
    // donc par rapport a une version rgba sans shader,
    // le travaille a faire ici est plus petit
    }

/*-----------------------------------*\
 |*		Tools	        	*|
 \*-----------------------------------*/

template<typename T>
void animer(Provider_I<T>* ptrProvider , double durationMaxS , bool isSynchronizeEnable)
    {
    const bool isVerbosityEnable = true;

    Animable_I<T>* ptrAnimable = ptrProvider->createAnimable();

    AnimatorImage<T> animator(ptrAnimable, isVerbosityEnable, isSynchronizeEnable, durationMaxS);
    animator.run();

    delete ptrAnimable;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

