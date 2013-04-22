#ifndef FUNDACION_H_
#define FUNDACION_H_

#include <iostream>
#include "Persona.h"
#include <vector>

using namespace std;

class Fundacion
{
public:
	//Constructores
	//Contructor por defecto
	Fundacion();
	//Contructor explicito
	Fundacion(string nombre, float saldo);

	//getters y setters
	string GetNombrePresidente();
	string GetNombreFundacion();
	float  GetSaldo();

	void  SetSaldo(float saldo);
	void SetNombreFundacion(string nombre);
	bool SetNombrePresidente(string dni);

	//Operaciones permitidas
	bool IngresarDinero(float cantidad);
	bool RetirarDinero(float cantidad);
	bool AgregarMiembro(Persona &p);
	bool DesligarMiembro(string dni);
	int BuscarMiembro(string dni);
	void ImprimirLista();

	//Sobrecarga de operadores (Metodos miembro)
	//Sacar e ingresar dinero con operadores aritmeticos
	bool operator+(int cantidad);
	bool operator-(int cantidad);

	//Añadir y borrar miembros con operadores aritmeticos
	bool operator+(Persona &p);
	bool operator-(string dni);

	//Mostrar los datos de una fundacion
	friend ostream& operator<<(ostream &out, Fundacion &f);
private:
	string nombre, presidente;
	float saldo;
	vector<Persona> miembros;
};

#endif /* FUNDACION_H_ */
