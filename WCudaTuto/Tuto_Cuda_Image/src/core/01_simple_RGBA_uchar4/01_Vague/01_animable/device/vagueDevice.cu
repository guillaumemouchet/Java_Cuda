#include "Thread2D.cu.h"
#include "cudas.h"

#include "VagueMath.cu.h"

#include "Indices.cu.h"

// Attention : 	Choix du nom est impotant!
//		VagueDevice.cu et non Vague.cu
// 		Dans ce dernier cas, probl�me de linkage, car le nom du .cu est le meme que le nom d'un .cpp (host)
//		On a donc ajouter Device (ou n'importequoi) pour que les noms soient diff�rents!

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

__global__ void vague(uchar4* tabPixelsGM , uint w , uint h , int t)
    {
    VagueMath vagueMath(w, h, t);

    const int WH = w * h;
    const int TID = Thread2D::tid();
    const int NB_THREAD = Thread2D::nbThread();

    int i;	// in [0,h[
    int j; 	// in [0,w[

    int s = TID;  // in [0,...
    while (s < WH)
	{
	Indices::toIJ(s, w, &i, &j); 	// update (i, j)

	vagueMath.colorIJ(&tabPixelsGM[s], i, j); 	// update ptrDevPixels[s]

	s += NB_THREAD;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

