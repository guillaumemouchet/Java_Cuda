#pragma once

#include "Provider_float4_HSBA_A.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class DamierHSBAFloatProvider: public Provider_float4_HSBA_A
    {
    public:

	/**
	 * Override
	 */
	virtual Grid grid();

	/**
	 * Override
	 */
	virtual Animable_I<float4>* createAnimable(const Grid& grid , bool isVerbose = false);

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

