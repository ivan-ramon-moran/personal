#ifndef PERSONA_H_
#define PERSONA_H_

#include <iostream>

using namespace std;

class Persona
{
public:
	//Constructores
	//Contructor por defecto.
	Persona();
	//Conctructor explicito
	Persona(string dni, string nombre, string apellido1, string apellido2);

	//Getters
	string GetDNI() const; //Devuelve el dni
	string GetApellido1() const; //Develve el primer apellido
	string GetApellido2() const; //Devuelve el segundo apellido
	string GetNombre() const; //Devuelve el nombre

	//Setters
	void SetDNI(string dni); //Establece el dni
	void SetApellido1(string apellido1); //Establece el primer apellido
	void SetApellido2(string apellido2); //Establece el segundo apellido
	void SetNombre(string nombre); //Establece el nombre

	//Sobrecarga de operadores
	/*Sobrecarga del operador de flujo << que nos permite imprimir los datos de una persona de la
	forma cout << persona;*/
	friend ostream& operator<<(ostream &out, const Persona &p);
private:
	string dni, nombre, apellido1, apellido2;
};

#endif /* PERSONA_H_ */
