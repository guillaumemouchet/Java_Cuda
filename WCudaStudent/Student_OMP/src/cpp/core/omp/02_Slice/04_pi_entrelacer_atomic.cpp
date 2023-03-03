#include <omp.h>
#include <Omps.h>

#include "00_pi_tools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerAtomic_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPEntrelacerAtomic(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerAtomic_Ok(int n)
    {
    return isAlgoPI_OK(piOMPEntrelacerAtomic, n, "Pi OMP Entrelacer atomic");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * Bonne performance, si!
 */
double piOMPEntrelacerAtomic(int n)
    {
    const double DX = 1 / (double)n;
    const int NB_THREAD = Omps::setAndGetNaturalGranularity();
    double sum = 0;
    //reduction intra thread
#pragma omp parallel
	{
	const int TID = Omps::getTid();

	int s = TID;

	double sumThread = 0;

	while (s < n)
	    {

	    double xs = s * DX;
	    sumThread += fpi(xs);
	    s += NB_THREAD;

	    }

	//Section critique
#pragma omp atomic
	sum += sumThread;

	}

    return sum * DX;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

