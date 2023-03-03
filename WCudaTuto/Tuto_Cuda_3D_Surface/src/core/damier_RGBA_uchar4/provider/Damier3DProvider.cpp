#include <iostream>

#include "Grid.h"
#include "Hardware.h"
#include "Maths.h"

#include "Damier3D_RGBA.h"
#include "Damier3DProvider.h"

#include "DomainMath3D_GPU.h"

using gpu::DomainMath3D;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * static
 */
SurfaceStrip_I* Damier3DProvider::createSurfaceStrip()
    {
    // Dimension "Image" en noeud
    uint w = 100;
    uint h = w;	// contrainte temporaire! Doit eter carrer, sinon bug!

    // Animation
    float dt = 2 * PI / 1000; // animation

    // Para de math
    int k = 2;

    // Domaine init
    double x1 = 0;
    double x2 = 2 * PI;

    double y1 = 0;
    double y2 = 2 * PI;

    double z1 = -1;
    double z2 = 1;

    DomainMath3D domaineMath(x1, x2, y1, y2, z1, z2); // Attention ordre, pas idem DomainMath2D, ici x1,x2, ...

    // Grid Cuda
    int mp = Hardware::getMPCount();
    int coreMP = Hardware::getCoreCountMP();

    dim3 dg(mp, 2, 1);  		// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
    dim3 db(coreMP, 2, 1);   	// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
    Grid grid(dg, db);

    // voir aussi le RenderMode dans mainCore.cpp

    return new Damier3D_RGBA(grid, w, h, domaineMath, dt, k); // Model
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

