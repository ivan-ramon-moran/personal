/*
 * Persona.cpp
 *
 *  Created on: 17/04/2013
 *      Author: k3rnel
 */

#include "Persona.h"

//Constructores
//Contructor por defecto
Persona::Persona(){}

//Contructor explicito
Persona::Persona(string dni, string nombre, string apellido1, string apellido2)
{
	//Asignamos DNI, nombre y apellidos a la persona que estamos creando mediante setters.
	SetDNI(dni);
	SetNombre(nombre);
	SetApellido1(apellido1);
	SetApellido2(apellido2);
}

//Getters y Setters
string Persona::GetDNI()
{
	return this->dni;
}

void Persona::SetDNI(string dni)
{
	this->dni = dni;
}

string Persona::GetNombre()
{
	return this->nombre;
}

void Persona::SetNombre(string nombre)
{
	this->nombre = nombre;
}

string Persona::GetApellido1()
{
	return this->apellido1;
}

void Persona::SetApellido1(string apellido1)
{
	this->apellido1 = apellido1;
}

string Persona::GetApellido2()
{
	return this->apellido2;
}

void Persona::SetApellido2(string apellido2)
{
	this->apellido2 = apellido2;
}

ostream& operator<<(ostream &out, const Persona &p)
{
	/*Sobrecarga del operador de flujo << que nos permite imprimir los datos de una persona de la
	forma cout << persona;*/
	out << "Nombre: " << p.nombre << "\n" << "Primer apellido: " << p.apellido1 << "\n"
		<< "Segundo apellido: " << p.apellido2 << "\n"
		<< "DNI: " << p.dni;
}
