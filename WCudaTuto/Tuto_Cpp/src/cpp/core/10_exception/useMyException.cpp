#include <stdlib.h>
#include <iostream>
#include <assert.h>

#include "MyException.h"

using std::cout;
using std::cerr;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/



/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void useMyException(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void use1(void);
static void use2(void);
static void use2Enfant(void);

static void exampleThrowMyException(void);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void useMyException(void)
    {
    use1();
    use2();

    // example non catcher
	{
	//exampleThrowMyException();

	// code n'arrivera jamais ici!
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void use1(void)
    {
    try
	{
	exampleThrowMyException();
	assert(false);
	}
    catch (MyException& e)
	{
	cerr << e << endl;

	cerr << e.what() << endl;
	}
    }

void use2(void)
    {
    try
	{
	use2Enfant();
	assert(false);
	}
    catch (MyException& e)
	{
	cerr << e << endl;

	cerr << e.what() << endl;
	}
    }

void use2Enfant(void)
    {
    exampleThrowMyException();
    }

void exampleThrowMyException()
    {
    throw MyException("easy c++ exception");
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

