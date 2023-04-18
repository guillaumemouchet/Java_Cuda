#include "Thread2D.cu.h"
#include "cudas.h"

#include "real.h"
#include "MandelbrotMath.cu.h"

#include "DomaineMath.h"
#include "Indices.cu.h"


/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

__global__ void mandelbrot(uchar4* tabPixelsGM , uint w , uint h , DomaineMath domaineMath , int n)
    {
    MandelbrotMath mandelbrotMath(n);

    // TODO Mandelbrot GPU :
    //
    // entrelacement
    // s -> (i,j) -> (x,y)
    // appeler colorXY

    const int TID = Thread2D::tid();
    const int NB_THREAD = Thread2D::nbThread();
    const int WH = w * h;

    int s = TID;
    int i = 0;
    int j = 0;

    double x;
    double y;

    while (s < WH)
    	{
    	Indices::toIJ(s, w, &i, &j);
    	domaineMath.toXY(i, j, &x, &y);
    	mandelbrotMath.colorXY(&tabPixelsGM[s], (real)x, (real)y);
    	s += NB_THREAD;
    	}

    //domaineMath.toXY(i, j, &x, &y); // x et y doivent etre en double! Caster ensuite en real lors du passage à colorXY

    // Probleme : Choix a faire pour le type de (x,y) :
    //
    //			- Travailler en float pour plus de performance?
    //			- Travailler en double pour pouvoir zoomer plus loin dans le fractale?
    //
    // Solution : Travailler avec le typedef real definit dans "real.h"
    //		  Specifier dans "real.h" si vous souhaitez travailler en float ou en double
    //	          Ainsi on passe facilement et proprement d'une version float a une version double
    //
    // Note : domaineMath.toXY travaille lui toujours en double pour vous permettre les deux possibilites ci-dessus
    //
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
