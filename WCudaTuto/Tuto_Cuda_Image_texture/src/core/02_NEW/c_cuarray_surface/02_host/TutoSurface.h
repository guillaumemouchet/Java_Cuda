#pragma once

#include <iostream>
#include "cudas.h"

#include "IteratorImageGray_I.h"
#include "Animable_I.h"
#include "Surface2D.h"

using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class TutoSurface: public Animable_I<uchar>
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	TutoSurface(const Grid& gridDilatation , IteratorImageGray_I* ptrIteratorImage , uint seuil0255);
	virtual ~TutoSurface(void);

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/*-------------------------*\
	|*   Override Animable_I   *|
	 \*------------------------*/

	/**
	 * Call periodicly by the api
	 */
	virtual void process(uchar* tabPixelsGM , uint w , uint h , const DomaineMath& domaineMath);

	/**
	 * Call periodicly by the api
	 */
	virtual void animationStep();

    public:

	static Grid bestGridSeuillage();

    private:

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	Grid gridSeuillage;
	Grid gridDilatation;
	uint seuil0255;

	// Tools
	IteratorImageGray_I* ptrIteratorImage;
	int wh;
	size_t sizeImage;

	// Tools image
	uchar* tabPixelVideo;
	uchar* tabPixelVideoGM;
	Surface2D<uchar> surface2D;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
