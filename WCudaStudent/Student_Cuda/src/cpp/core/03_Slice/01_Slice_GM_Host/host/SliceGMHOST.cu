#include "SliceGMHOST.h"

#include <iostream>
#include <assert.h>

#include "GM.h"
#include "Maths.h"
#include "Hardware.h"
#include "Kernel.h"

using std::cout;
using std::endl;
using std::to_string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void reductionIntraThreadGMHOST(float* tabGM,int nbSlice);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

SliceGMHOST::SliceGMHOST(Grid grid , int nbSlice , double* ptrPiHat , bool isVerbose) :
	RunnableGPU(grid, "SliceGM-HOST-" + to_string(nbSlice), isVerbose), // classe parente

	dg(grid.dg), //
	db(grid.db),
	nbSlice(nbSlice), //
	ptrPiHat(ptrPiHat)
    {
    // ntabGM
	{
	this->nTabGM = grid.threadCounts();
	// Warning : Advanced : Et si plus de threads que slices? complique! (pas utile de le coder)
	}

    // MM
	{
	this->sizeTabGM = nTabGM*sizeof(float);//  [octet]
	GM::malloc(&tabGM, sizeTabGM);
	}
    }

SliceGMHOST::~SliceGMHOST(void)
    {
    //MM (device free)
	{
	GM::free(tabGM);
	}
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

/**
 * <pre>
 * Idea globale
 *
 *	Etape 0 : Promotion d'un tableau en GM (MemoryManagement MM)		(Dans le constructeur)
 * 	Etape 1 : Reduction intra-thread dans un tableau promu en GM
 * 	Etape 2 : Copy du tableau coter host
 * 	Etape 3 : Reduction  du tableau coter host
 * 	Etape 4 : Destruction GM						(Dans le destructeur)
 *
 * </pre>
 */
void SliceGMHOST::run()
    {
    // call the kernel
    reductionIntraThreadGMHOST<<<dg,db>>>(tabGM,nbSlice);

    reductionHost();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * Reduction paralle sur cpu du tableau promu en GM, ramener coter host
 */
void SliceGMHOST::reductionHost()
    {
    // 1) Creer un tableau de bonne dimension (sur la pile, possible ssi petit, sinon sur la tas)
    float tab[nTabGM];

    // 2) Transferer la tabGM dedans
    double totalSomme = 0;


    GM::memcpyDToH(tab, tabGM, sizeTabGM);

    // 3) Reduction sequentiel cote host

    for(int i = 0; i<nTabGM; i++)
	{
	totalSomme = totalSomme +tab[i];
	}

    // 4) finalisation du calcul de ptrPiHat
    //totalSomme = totalSomme/nbSlice;

    *ptrPiHat = totalSomme;


    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
