#ifndef REVISTA_H_
#define REVISTA_H_

#include <iostream>
#include "Publicacion.h"

using namespace std;

class Revista:public Publicacion
{
public:
	//Contructores
	//Contructor por defecto
	Revista();
	//Contructor explicito
	void IniciarRevista(long long codigo, string editor, Fecha &fecha, string titulo, string periodicidad, int num_ejemplar);


	//Getter y Setters
	//Para el titulo
	string GetTitulo();
	void SetTitulo(string titulo);

	//Para el atributo periodicidad
	string GetPeriodicidad() const;
	void SetPeriodicidad(string periodicidad);

	//Para el atributo num_ejemplar
	int GetNumEjemplar() const;
	void SetNumEjemplar(int num_ejemplar);

	//Sobrecarga de operadores
	//Sobrecarga del operador << para poder mostrar los datos de un objeto tipo Revista por pantalla
	friend ostream& operator<<(ostream &out, const Revista &revista);
private:
	string titulo;
	string periodicidad;
	int num_ejemplar;
};

#endif /* REVISTA_H_ */
