#ifndef PERSONA_H_
#define PERSONA_H_

#include <iostream>

using namespace std;

class Persona
{
public:
	//Constructores
	Persona();
	//Conctructor explicito
	Persona(string dni, string nombre, string apellido1, string apellido2);

	//Getters
	string GetDNI();
	string GetApellido1();
	string GetApellido2();
	string GetNombre();

	//Setters
	void SetDNI(string dni);
	void SetApellido1(string apellido1);
	void SetApellido2(string apellido2);
	void SetNombre(string nombre);

	//Sobrecarga de operadores
	/*Sobrecarga del operador de flujo << que nos permite imprimir los datos de una persona de la
	forma cout << persona;*/
	friend ostream& operator<<(ostream &out, const Persona &p);
private:
	string dni, nombre, apellido1, apellido2;
};

#endif /* PERSONA_H_ */
