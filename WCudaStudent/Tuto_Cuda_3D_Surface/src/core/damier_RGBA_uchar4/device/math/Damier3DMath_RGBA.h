#pragma once

#include <math.h>

#include "Calibreur.cu.h"
#include "Colors.cu.h"

#define DEUX 2.f
#define QUATRE 4.f
#define ZERO 0.f

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class Damier3DMath_RGBA
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ Damier3DMath_RGBA(int n) :
		n(n)
	    {
	    // rien
	    }

	// constructeur copie automatique car pas pointeur dans
	//	DamierMath
	// 	calibreur
	// 	IntervalF

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void process(float3* ptrSommet , uchar4* ptrColor , float x , float y , float t)
	    {
	    int k = suite(x, y);
	    float h01 = k / (float)(n - 1);

	    ptrSommet->x = x;
	    ptrSommet->y = y;
	    ptrSommet->z = z(h01);

	    colorXY(ptrColor, k);
	    }

    private:__device__
	void colorXY(uchar4* ptrColorIJ , int k)
	    {
	    // TODO Mandelbrot GPU

	    float h01 = k / (float)(n - 1);

	    if (k > n)
		{
		ptrColorIJ->x = 0;
		ptrColorIJ->y = 0;
		ptrColorIJ->z = 0;
		ptrColorIJ->w = 255;
		}
	    else
		{
		Colors::HSB_TO_RVB(h01, ptrColorIJ);
		}
	    }

	__inline__
	__device__
	int suite(float x , float y)
	    {
	    // TODO Mandelbrot GPU

	    // Utiliser dans vos formules les variable :
	    //
	    //		DEUX
	    //		QUATTRE
	    //		ZERO
	    //
	    // definit au debut de ce fichier. Est-utile pour  passer facilement d'une version fp64 (double) fp32(float) fp16(half)

	    // Calculer la suite en (x,y) jusqu'à n, à moins que critere arret soit atteint avant
	    // return le nombre d'element de la suite calculer, ie un entier

	    int indice = ZERO;
	    float xz = ZERO;
	    float yz = ZERO;
	    float xzCopy = ZERO;

	    do
		{
		xzCopy = xz;
		xz = (xz * xz - yz * yz) + x;
		yz = DEUX * xzCopy * yz + y;
		indice++;
		}while((xz * xz + yz * yz) < QUATRE && indice <= n);

	    return indice;
	    }
	__device__
	float z(float h01)
	    {
	    const int M = 8;	    //1 ou 8 (ici fixe)
	    return logs(h01, M) + 0.5f;
	    }
	__device__
	float logs(float h01 , const int M)
	    {
	    float z = h01;
	    for (int i = 0; i <= M; i++)
		{
		z = log(z + 1.0f);
		}
	    return z;
	    }
	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	int n;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
