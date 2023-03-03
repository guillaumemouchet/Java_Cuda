#include "Thread2D.cu.h"
#include "Thread1D.cu.h"
#include "cudas.h"
#include "Maths.h"

#include "ifelse.cu.h"
#include "Edge.cu.h"
#include "Indices.cu.h"
#include "SousImageIterator.cu.h"

/*----------------------------------------------------------------------*\
 |*			Declaration / private				*|
 \*---------------------------------------------------------------------*/

static __device__ void kDilatationV1(uchar* tabPixelsGM , uchar* tabPixelVideoSeuillerGM , uint w , uint h);
static __device__ void kDilatationV2(uchar* tabPixelsGM , uchar* tabPixelVideoSeuillerGM , uint w , uint h);
static __device__ void kDilatationV3(uchar* tabPixelsGM , uchar* tabPixelVideoSeuillerGM , uint w , uint h);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

__global__ void kDilatation(uchar* tabPixelsGM , uchar* tabPixelVideoSeuillerGM , uint w , uint h)
    {
   // kDilatationV1(tabPixelsGM, tabPixelVideoSeuillerGM, w, h);
  //  kDilatationV2(tabPixelsGM, tabPixelVideoSeuillerGM, w, h);
    kDilatationV3(tabPixelsGM, tabPixelVideoSeuillerGM, w, h);
    }

/*----------------------------------------------------------------------*\
 |*			private 					*|
 \*---------------------------------------------------------------------*/

/*-------------*\
 |*	v1	*|
 \*------------*/

__device__ void kDilatationV1(uchar* tabPixelsGM , uchar* tabPixelVideoSeuillerGM , uint w , uint h)
    {
    const int TID = Thread2D::tid();
    const int NB_THREAD = Thread2D::nbThread();
    const int WH = w * h;

    Edge edge(w, h, 1); // debug bord=100

    int s = TID;
    int sum;
    int i;
    int j;
    while (s < WH)
	{
	Indices::toIJ(s, w, &i, &j);
	if (!edge.isInEdge(i, j)) // thread divergence
	    {
	    sum = 0;

	    // read
		{
		// ligne dessus
		sum += tabPixelVideoSeuillerGM[s - w - 1];
		sum += tabPixelVideoSeuillerGM[s - w];
		sum += tabPixelVideoSeuillerGM[s - w + 1];

		// meme ligne, sauf moi meme
		sum += tabPixelVideoSeuillerGM[s - 1];
		sum += tabPixelVideoSeuillerGM[s + 1];

		// ligne dessous
		sum += tabPixelVideoSeuillerGM[s + w - 1];
		sum += tabPixelVideoSeuillerGM[s + w];
		sum += tabPixelVideoSeuillerGM[s + w + 1];
		}

	    // write
	    tabPixelsGM[s] = ifelse(sum > 1, 255, 0);
	    }

	// next
	s += NB_THREAD;
	}
    }

/*-------------*\
 |*	v2	*|
 \*------------*/

/**
 * sans if
 * sans thead-divergence
 */
__device__ void kDilatationV2(uchar* tabPixelsGM , uchar* tabPixelVideoSeuillerGM , uint w , uint h)
    {
    const int TID = Thread2D::tid();
    const int NB_THREAD = Thread2D::nbThread();

    //	Difficulter:
    //
    //		(O1)	Partern entrelacement sur la zone centrale (sans if)
    //
    // Solution:
    //
    //		(S1) Step A: on fabrique s puis (i,j) de la petiteImage
    //	             Step B: on fabrique ss puis (i.j) de la grandeImage
    // Definition:
    //
    //		(D1) zoneCentrale=image-bord ou bord depend fu rayon du kernel de convolution
    //
    //		(D2) petiteImage= image de base, de taille de la zone centrale, avec le coin en haut a gauche au meme endroit que image de bas
    //
    //		(D3) petimeImageCentrale = petiteImage translater en i et j de rayon et rayon
    //
    //		(D4) Grande image = image de base wxh
    //
    //	Notes:
    //
    //		(N1) Le resultat de la convolution doit etre calculer que sur petimeImageCentrale
    //
    //		(N2) petiteImage et petimeImageCentrale sont de meme taille, mais pas eu meme endroit
    //

    const int BORD = 1; // debug 100, voir zone centrale
    const int W_INTERNE = w - 2 * BORD;
    const int H_INTERNE = h - 2 * BORD;
    const int WH_INTERNE = W_INTERNE * H_INTERNE;

    int sum;
    int s = TID;
    int i;
    int j;
    while (s < WH_INTERNE) // on parcours autant de pixels que contient petiteImage
	{
	/*--------------------------------------*\
	 |*	preparation indice sous image	*|
	 \*-------------------------------------*/

	// Step A: (i,j,s) petite image:
	Indices::toIJ(s, W_INTERNE, &i, &j); // on fabrique (i,j) de la petite image

	// Step B: (i,j,ss) grande image:
	// Step B.1: on fabrique le (i,j) correspondant de la grande image par translation dans la zone centrale
	i += BORD;
	j += BORD;
	// Step B.2: on fabrique ss de la grande image en partant de (i,j) translater
	int ss = (i * w) + j;

	// resumer:
	//	avant (i,j,s) petiteImage
	//	apres (i,j,ss) grandeImage

	/*--------------------------------------*\
	|*	travail avec indice sous image	*|
	 \*-------------------------------------*/

	// travai avec (i,j,ss)
	sum = 0;

	//read
	    {
	    // ligne dessus
	    sum += tabPixelVideoSeuillerGM[ss - w - 1];
	    sum += tabPixelVideoSeuillerGM[ss - w];
	    sum += tabPixelVideoSeuillerGM[ss - w + 1];

	    // meme ligne, sauf moi meme
	    sum += tabPixelVideoSeuillerGM[ss - 1];
	    sum += tabPixelVideoSeuillerGM[ss + 1];

	    // ligne dessous
	    sum += tabPixelVideoSeuillerGM[ss + w - 1];
	    sum += tabPixelVideoSeuillerGM[ss + w];
	    sum += tabPixelVideoSeuillerGM[ss + w + 1];
	    }

	// write
	tabPixelsGM[ss] = ifelse(sum > 1, 255, 0);
	//tabPixelsGM[ss] = tabPixelVideoSeuillerGM[ss]; // debug

	// next
	s += NB_THREAD;
	}
    }

/*-------------*\
 |*	v3	*|
 \*------------*/

/**
 * sans if
 * sans thead-divergence
 * idem v2, plus light (SousImageIterator contient l'approche ci-dessus de v2)
 */
__device__ void kDilatationV3(uchar* tabPixelsGM , uchar* tabPixelVideoSeuillerGM , uint w , uint h)
    {
    const int BORD = 1; // debug 100
    SousImageIterator it(w, h, BORD);

    int sum;
    int i;
    int j;
    int s;
    while (it.hasNext())
	{
	s = it.nextS(&i, &j);

	sum = 0;

	// read
	    {
	    // ligne dessus
	    sum += tabPixelVideoSeuillerGM[s - w - 1];
	    sum += tabPixelVideoSeuillerGM[s - w];
	    sum += tabPixelVideoSeuillerGM[s - w + 1];

	    // meme ligne, sauf moi meme
	    sum += tabPixelVideoSeuillerGM[s - 1];
	    sum += tabPixelVideoSeuillerGM[s + 1];

	    // ligne dessous
	    sum += tabPixelVideoSeuillerGM[s + w - 1];
	    sum += tabPixelVideoSeuillerGM[s + w];
	    sum += tabPixelVideoSeuillerGM[s + w + 1];
	    }

	// write
	tabPixelsGM[s] = ifelse(sum > 1, 255, 0);
	//tabPixelsGM[s] = tabPixelVideoSeuillerGM[s]; // ou 128 DEBUG
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

