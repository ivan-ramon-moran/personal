/*
 * ExcepcionPersonalizada.h
 *
 *  Created on: 15/05/2013
 *      Author: k3rnel
 */

#ifndef EXCEPCIONPERSONALIZADA_H_
#define EXCEPCIONPERSONALIZADA_H_

#include <exception>
#include <iostream>

using namespace std;

class ExcepcionPersonalizada: public exception
{
public:
	ExcepcionPersonalizada(string mensaje);
	const char* what() const throw();
    virtual ~ExcepcionPersonalizada() throw();
private:
	string mensaje;
};

#endif /* EXCEPCIONPERSONALIZADA_H_ */
