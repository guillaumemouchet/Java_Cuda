#include <DomainMath3D_GPU.h>
#include <Indices.cu.h>
#include <Thread2D.cu.h>

#include "math/Damier3DMath_RGBA.h"

using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void damier3DCuda(float3* tabVerticesXYZGM , uchar4* tabVerticesColorGM , int w , int h , DomainMath3D domaineMath , float t);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * w nbPoint en x
 * h nbPoint en y
 */
__global__ void damier3DCuda(float3* tabVerticesXYZGM , uchar4* tabVerticesColorGM , int w , int h , DomainMath3D domaineMath , float t)
    {

    const int n = (int)t;
    Damier3DMath_RGBA damierMath(n);
    const int TID = Thread2D::tid();
    const int NB_THREAD = Thread2D::nbThread();

    const int WH = w * h;

    uchar4 color;
    float3 sommet;

    float x;
    float y;
    float DX;
    float DY;

    int vertexI;
    int vertexJ;

    domaineMath.delta(w, h, &DX, &DY);

    int s = TID;
    while (s < WH)
	{
	Indices::toIJ(s, w, &vertexI, &vertexJ); // update (vertexI, vertexJ)

	domaineMath.toXY(DX, DY, vertexI, vertexJ, &x, &y);

	damierMath.process(&sommet, &color, x, y, n); // update sommet

	tabVerticesColorGM[s] = color;
	tabVerticesXYZGM[s] = sommet;

	s += NB_THREAD;
	}

    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
