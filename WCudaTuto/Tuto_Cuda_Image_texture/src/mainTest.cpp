#include <stdlib.h>
#include <iostream>
#include <string>
#include <iomanip>

#include "CppTest.h"
#include "cudas.h"
#include "Folders.h"
#include "Chrome.h"

#include "Videos.h"

#include "TestWarmup.h"

#include "TestTutoTextureGM.h"
#include "TestTutoTextureCuarray.h"
#include "TestTutoSurface.h"

using std::string;
using std::cout;
using std::cerr;
using std::endl;

using Test::Suite;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainTest()
    {
    Videos::preloadONE();

    Suite testSuite;

    testSuite.add(std::auto_ptr < Suite > (new TestWarmup()));
    testSuite.add(std::auto_ptr < Suite > (new TestTutoTextureGM()));
    testSuite.add(std::auto_ptr < Suite > (new TestTutoTextureCuarray()));
    testSuite.add(std::auto_ptr < Suite > (new TestTutoSurface()));

// run
	{
	string folder = "./out";
	string title = "testAll"; // see above, title list
	string fileHTML = title + ".html";

	Folders::mkdirP(folder);

	int result = CppTest::run(folder, fileHTML, title, testSuite, OutputType::HTML); // HTML CONSOLE

	Chrome::showHTML(folder, fileHTML); // to be commented if OutputType::CONSOLE

	return result;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

