#include <omp.h>
#include <Omps.h>

#include "00_pi_tools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerCritical_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPEntrelacerCritical(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerCritical_Ok(int n)
    {
    return isAlgoPI_OK(piOMPEntrelacerCritical, n, "Pi OMP Entrelacer critical");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

double piOMPEntrelacerCritical(int n)
    {
    const double DX = 1 / (double)n;
    const int NB_THREAD = Omps::setAndGetNaturalGranularity();

    double sum = 0;

//R?duction intra-threads
#pragma omp parallel
	{
	const int TID = Omps::getTid();

	int s = TID;
	double sumThread = 0;
	double xs;

	while (s < n)
	    {
	    xs = s * DX;
	    sumThread += fpi(xs);

	    s += NB_THREAD;
	    }

#pragma omp critical
	    {
	    sum += sumThread;
	    }

	}

    return DX * sum;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

