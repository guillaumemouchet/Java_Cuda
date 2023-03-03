#include "Thread2D.cu.h"
#include "Thread1D.cu.h"
#include "cudas.h"
#include "Maths.h"

#include "Calibreur.cu.h"
#include "Indices.cu.h"
#include "ifelse.cu.h"
#include "Edge.cu.h"

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/**
 * surf2d 	: read
 * tabPixelGM   : write
 *
 * Note: fait par exemple disparaitre les points noirs dans les bandes blanches de la route (pour video autoroute)
 */
__global__ void KDilatationSurf(uchar* tabPixelGM , cudaSurfaceObject_t surf2d , uint w , uint h)
    {
    const int WH = w * h;
    const int TID = Thread2D::tid();
    const int NB_THREAD = Thread2D::nbThread();

    // Edge edge(w, h, 1);

    int s = TID;
    int i;
    int j;
    uchar pixelS;
    int sum;
    while (s < WH)
	{
	Indices::toIJ(s, w, &i, &j);

	surf2Dread(&pixelS, surf2d, j, i); // warning (j,i) et non (i,j)

	//if (!edge.isInEdge(i, j)) // pas besoin avec cudaBoundaryModeClamp ci-dessous
	    {
	    sum = 0;

	    // read
		{
		// ligne dessus
		sum += surf2Dread < uchar > (surf2d, j - 1, i - 1, cudaBoundaryModeClamp);
		sum += surf2Dread < uchar > (surf2d, j, i - 1, cudaBoundaryModeClamp);
		sum += surf2Dread < uchar > (surf2d, j + 1, i - 1, cudaBoundaryModeClamp);

		// meme ligne, sans moi
		sum += surf2Dread < uchar > (surf2d, j - 1, i, cudaBoundaryModeClamp);
		sum += surf2Dread < uchar > (surf2d, j + 1, i, cudaBoundaryModeClamp);

		// ligne dessous
		sum += surf2Dread < uchar > (surf2d, j - 1, i + 1, cudaBoundaryModeClamp);
		sum += surf2Dread < uchar > (surf2d, j, i + 1, cudaBoundaryModeClamp);
		sum += surf2Dread < uchar > (surf2d, j + 1, i + 1, cudaBoundaryModeClamp);
		}

	    // write
	    tabPixelGM[s] = ifelse(sum >= 1, (uchar)255, pixelS);
	    //tabPixelGM[s] = pixelS; // debug
	    }

	// next
	s += NB_THREAD;
	}
    }

// Note:
// 	on pourrait prendre un voisinage v8 avec une (ou plusieurs) aurole de plus, autour du pixels,
// 	pour faire disparaitre encore plus de zone noir dans la bande blanche, quitte a fire une errosion apres
//	Voir KDilatationN ci-dessous

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

