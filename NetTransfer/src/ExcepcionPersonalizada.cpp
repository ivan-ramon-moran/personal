/*
 * ExcepcionPersonalizada.cpp
 *
 *  Created on: 15/05/2013
 *      Author: k3rnel
 */

#include "ExcepcionPersonalizada.h"

ExcepcionPersonalizada::ExcepcionPersonalizada(string mensaje)
{
	this->mensaje = mensaje;
}

const char* ExcepcionPersonalizada::what() const throw()
{
	return mensaje.c_str();
}

ExcepcionPersonalizada::~ExcepcionPersonalizada() throw()
{

}
