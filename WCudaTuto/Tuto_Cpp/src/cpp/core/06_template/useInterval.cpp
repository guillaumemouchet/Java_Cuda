#include <stdlib.h>
#include <iostream>

#include "Interval.h"
#include <math.h>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void useTemplate(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void use0(void);
static void use1(void);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void useTemplate(void)
    {
    cout << "\nInterval : useTemplate" << endl;

    use0();
    use1();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void use0(void)
    {
    Interval<double> interval(M_PI, 2 * M_PI);
    interval.print();
    }

void use1(void)
    {
    Interval<int> interval(1, 2);

    interval.print();
    interval.translate(10);
    interval.print();
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

