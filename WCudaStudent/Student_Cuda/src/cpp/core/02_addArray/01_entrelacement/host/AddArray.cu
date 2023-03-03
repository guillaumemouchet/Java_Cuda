#include "AddArray.h"

#include <assert.h>
#include <GM.h>
#include <GM_MemoryManagement.h>
#include <iostream>

using std::cout;
using std::endl;
using std::to_string;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void addArray(float* ptrDevV1, float* ptrDevV2, float* ptrDevW,int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

AddArray::AddArray(const Grid& grid , float* ptrV1 , float* ptrV2 , float* ptrW , int n) :
	ptrV1(ptrV1), //
	ptrV2(ptrV2), //
	ptrW(ptrW), //
	n(n), // this.n = n;
	dg(grid.dg), //
	db(grid.db)
    {
    this->sizeVector = n * sizeof(float); // octet

    // MM (malloc Device)
	{
	GM::malloc(&ptrDevV1, sizeVector);
	GM::malloc(&ptrDevV2, sizeVector);
	GM::malloc(&ptrDevW, sizeVector);

	}

    }

AddArray::~AddArray(void)
    {
    //MM (device free)
	{
	GM::free(ptrDevV1);
	GM::free(ptrDevV2);
	GM::free(ptrDevW);

	}
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

/**
 * override
 */
void AddArray::run()
    {
    // MM (copy Host->Device)
	{
	GM::memcpyHToD(ptrDevV1, ptrV1, sizeVector); //ptrDevV1 = ptrV1 <-
	GM::memcpyHToD(ptrDevV2, ptrV2, sizeVector);

	}

    // call kernel // assynchrone
    addArray<<<dg,db>>>(ptrDevV1, ptrDevV2, ptrDevW, n);
    //Kernel::synchronize();// inutile

    // MM (Device -> Host)
	{
	// MM barier de synchronisation implicite
	GM::memcpyDToH(ptrW, ptrDevW, sizeVector);
	}
    }

/*----------------------------------------------------------------------*\
|*			End	 					*|
 \*----------------------------------------------------------------------*/
