#include "MyException.h"

#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::to_string;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur		*|
 \*-------------------------------------*/

/**
 * constructeur dominant
 */
MyException::MyException(string msg) :
	msg(msg)
    {
    this->whatMessage = new string("[MyException] : " + msg);
    }

MyException::MyException() :
	MyException(EMPTY)
    {
    // rien de plus
    }

MyException::~MyException()
    {
    delete whatMessage;
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

string MyException::getMessage()
    {
    return msg;
    }

/**
 * override
 */
const char* MyException::what() const throw ()
    {
    return whatMessage->c_str();
    }

/**
 * friend
 */
ostream& operator <<(ostream &stream, const MyException &myException)
    {
    stream << "[MyException] : " + myException.msg << endl;

    return stream;
    }

/**
 * static
 */
string MyException::EMPTY = "";

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

