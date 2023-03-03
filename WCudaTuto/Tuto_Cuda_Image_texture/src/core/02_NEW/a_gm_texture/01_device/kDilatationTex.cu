#include "Thread2D.cu.h"
#include "Thread1D.cu.h"
#include "cudas.h"
#include "Maths.h"
#include "ifelse.cu.h"
#include "Indices.cu.h"

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/**
 * input  : tex2dGM 		(Image seuiller)
 * output : tabPixelsGM 	(Image ecran)
 */
__global__ void kDilatationTex(uchar* tabPixelsGM , cudaTextureObject_t tex2dGM , uint w , uint h)
    {
    const int TID = Thread2D::tid();
    const int NB_THREAD = Thread2D::nbThread();
    const int WH = w * h;

    int s = TID;
    int i;
    int j;
    int sum;
    while (s < WH)
	{
	Indices::toIJ(s, w, &i, &j);

	sum=0;

	// read
	    {
	    // ligne dessus
	    sum += tex2D < uchar > (tex2dGM, j - 1, i - 1);  // warning: orde i et j : tex2D(j,i) et non (i,j)
	    sum += tex2D < uchar > (tex2dGM, j, i - 1);
	    sum += tex2D < uchar > (tex2dGM, j + 1, i - 1);

	    // meme ligne, sauf moi meme
	    sum += tex2D < uchar > (tex2dGM, j - 1, i);
	    sum += tex2D < uchar > (tex2dGM, j + 1, i);

	    // ligne dessous
	    sum += tex2D < uchar > (tex2dGM, j - 1, i + 1);
	    sum += tex2D < uchar > (tex2dGM, j, i + 1);
	    sum += tex2D < uchar > (tex2dGM, j + 1, i + 1);
	    }

	// write
	tabPixelsGM[s] = ifelse(sum > 1, 255, 0);
	//tabPixelsGM[s]=tex2D < uchar > (tex2dGM, j, i); // debug

	// next
	s+=NB_THREAD;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

