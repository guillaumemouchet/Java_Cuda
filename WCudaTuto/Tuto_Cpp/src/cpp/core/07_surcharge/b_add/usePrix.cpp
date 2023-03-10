#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <assert.h>

#include "Prix.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/



/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void useSurchargeAdd(void);

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

void useSurchargeAdd(void)
    {
    cout << "\nPrix : useSurchargeAdd" << endl;

    use0();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void use0(void)
    {
    Prix prixVoiture(180, "porsche");
    Prix prixMaison(220, "maison");

    Prix prixTotal=prixVoiture+prixMaison;

    cout<<prixTotal.getPrix()<<endl;
    cout<<prixTotal.getObjet()<<endl;

    //check
    assert(prixTotal.getPrix() == 180+220);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

