#pragma once

#include "Provider_uchar4_A.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/**
 * Observation:
 * 	Les objets retournees sont sur le tas (2 ptr)
 *
 * Destruction:
 * 	4 cas d'utilisation:
 * 		- Image
 * 		- Animable
 * 		- ForceBrut
 * 		- Barivox
 *
 * 	Cas Image:
 * 		Le viewer s'occupe d'effacer:
 * 			- Image_I*
 * 			- Animable_I<uchar4>*
 * 	Cas Animable:
 *		L'animator detruit animable
 *
 * 	Cas ForceBrut:
 * 		Force brut utilise animator qui detruit animable
 *
 * 	Cas Barivox:
 * 		Barivox detruit
 *
 * 	Autre cas:
 * 		A vous de detruire les objets
 *
 */
class VagueProvider: public Provider_uchar4_A
    {
    public:

	/**
	 * Override
	 */
	virtual Grid grid();

	/**
	 * Override
	 */
	virtual Animable_I<uchar4>* createAnimable(const Grid& grid , bool isVerbose = false);


    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

