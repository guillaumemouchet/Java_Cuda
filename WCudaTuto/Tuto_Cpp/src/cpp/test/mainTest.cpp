#include <stdlib.h>
#include <fstream>
#include <string>

#include "CppTest.h"
//#include "Folders.h"
//#include "Chrome.h"

#include "TestCalculatrice.h"
#include "TestHello.h"

using std::cout;
using std::endl;
using std::string;
using std::auto_ptr;

using Test::Suite;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainTest(void)
    {
    Suite testSuite;

    testSuite.add(auto_ptr < Suite > (new TestCalculatrice()));
    testSuite.add(auto_ptr < Suite > (new TestHello()));

    // run
   	{
   	string folder = "./out";
   	string title = "testTutoCpp";
   	string fileHTML = title + ".html";

   	//Folders::mkdirP(folder);

   	int result = CppTest::run(folder, fileHTML, title, testSuite, OutputType::HTML); // HTML CONSOLE

   	//Chrome::showHTML(folder, fileHTML);// to be commented if OutputType::CONSOLE

   	return result;
   	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

