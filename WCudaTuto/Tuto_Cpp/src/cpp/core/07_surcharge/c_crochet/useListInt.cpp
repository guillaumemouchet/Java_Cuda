#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <assert.h>

#include "ListInt.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void useSurchargeCrochet(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void use0(void);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void useSurchargeCrochet(void)
    {
    cout << "\nListInt : useSurchargeCrochet" << endl;

    use0();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void use0(void)
    {
    int x = 1;
    int y = 2;

    ListInt list;
    assert(list.size() == 0);

    list.add(x);
    list.add(y);

    assert(list[0] == x);
    assert(list[1] == y);

    cout << list << endl;
    assert(list.size() == 2);

    int yy = list.pop();
    int xx = list.pop();

    assert(list.size() == 0);
    assert(xx == x);
    assert(yy == y);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

