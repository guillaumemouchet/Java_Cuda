#pragma once

#include "Provider_float_hue_A.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class DamierHueFloatProvider: public Provider_float_hue_A
    {
    public:

	/**
	 * Override
	 */
	virtual Grid grid();

	/**
	 * Override
	 */
	virtual Animable_I<float>* createAnimable(const Grid& grid , bool isVerbose = false);

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

