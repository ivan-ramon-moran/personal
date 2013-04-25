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
	string GetDNIPresidente() const;
	string GetNombreFundacion() const;
	float  GetSaldo() const;

	void  SetSaldo(float saldo);
	void SetNombreFundacion(string nombre);
	bool SetDNIPresidente(string dni);

	//Operaciones permitidas
	//Funcion que permite ingresar dinero.
	bool IngresarDinero(float cantidad);
	//Funcion que permite retirar dinero
	bool RetirarDinero(float cantidad);
	//Funcion que permite agregar un miembro
	bool AgregarMiembro(const Persona &p);
	//Funcion que permite eliminar un miebro
	bool DesligarMiembro(string dni);
	//Funcion que permite buscar a un miembro por su DNI.
	int BuscarMiembro(string dni);
	//Imprime una lista con los miembros de la fundacion.
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
