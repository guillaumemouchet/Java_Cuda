#pragma once

#include <iostream>
#include <exception>

using std::ostream;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/


class MyException: public std::exception
    {
	/*------------------------------------------------------------*\
	|*			Constructeur 				   *|
	 \*------------------------------------------------------------*/

    public:

	MyException(string msg);

	MyException();

	virtual ~MyException();

	/*------------------------------------------------------------*\
	|*			Methode 				  *|
	 \*------------------------------------------------------------*/

    public:

	string getMessage();

	/**
	 * override
	 */
	virtual const char* what() const throw ();

    private:

	/**
	 * surcharge <<
	 */
	friend ostream& operator <<(ostream &stream, const MyException &myException);

	/*------------------------------------------------------------*\
    |*			Attribut 				   *|
	 \*------------------------------------------------------------*/

    private:

	// Input
	string msg;

	// Output
	string *whatMessage;

	static string EMPTY;

    };

/*--------------------------------------*\
 |*		Example			*|
 \*-------------------------------------*/

/*
 int exemple()
 {
 try
 {
 throw DroneExceptionCBI();
 }
 catch (DroneExceptionCBI &e)
 {
 std::cout << "MyException caught" << std::endl;
 std::cout << e.what() << std::endl;
 }
 catch (std::exception &e)
 {
 //Other errors
 }
 }*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

