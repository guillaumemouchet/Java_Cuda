#pragma once

#include "Provider_float4_RGBA_A.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class DamierRGBAFloatProvider: public Provider_float4_RGBA_A
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

	/**
	 * Override facultatif
	 */
	ColorRGB_01 colorTitle();

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

