#include "AddArrayUse11.h"

#include "ArrayTools.h"
#include "AddArray.h"
#include "Limits.h"

#include "Maths.h"
#include "Hardware.h"

#include <iostream>
#include <iomanip>
#include <assert.h>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::setprecision;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

static const int N = 9;

/*--------------------------------------*\
|*		Constructor		*|
 \*-------------------------------------*/

AddArrayUse11::AddArrayUse11() : //
	grid(createGrid()), //
	n(N)
    {
    this->ptrV1 = ArrayTools::createV1(n);
    this->ptrV2 = ArrayTools::createV2(n);
    this->ptrW = new float[n];

    this->ptrAddArray11 = new AddArray11(grid, ptrV1, ptrV2, ptrW, n);
    }

AddArrayUse11::~AddArrayUse11()
    {
    delete ptrAddArray11;

    delete[] ptrV1;
    delete[] ptrV2;
    delete[] ptrW;
    }

/*--------------------------------------*\
|*		Methodes		*|
 \*-------------------------------------*/

bool AddArrayUse11::isOk()
    {
    this->ptrAddArray11->run();

    bool isOk = ArrayTools::isAddVector_Ok(ptrV1, ptrV2, ptrW, n);

    ArrayTools::print(ptrV1, n);
    ArrayTools::print(ptrV2, n);
    cout << "--------------------------------------------------------------------" << endl;
    ArrayTools::print(ptrW, n);
    cout << endl;

    cout << "[AddArray] : 1 <--> 1 : ";

    if (isOk)
	{
	cout << "Success!" << endl << endl;
	}
    else
	{
	cerr << "Failed!" << endl << endl;
	}

    return isOk;
    }

/*--------------------------------------*\
|*		Private			*|
 \*-------------------------------------*/

/**
 * static
 */
Grid AddArrayUse11::createGrid()
    {
    const bool IS_CHECK_HEURISTIC = false;

    dim3 dg(N, 1, 1); //la performance est immonde
    //Seule option noteamemnt si n es tpremier :  performance catastrophique
    //Heurisitque pas respectée et surtout tous les couerus par MPS sauf 1 sont des chômeurs
    dim3 db(1, 1, 1);// contrainte : produi<=1024
    Grid grid(dg, db, IS_CHECK_HEURISTIC);

    assert(grid.threadCounts() == N);

    return grid;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
