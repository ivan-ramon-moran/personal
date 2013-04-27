#ifndef LIBRO_H_
#define LIBRO_H_

#include <iostream>
#include "Publicacion.h"

using namespace std;

const string VERDE = "\033[22;32m";
const string AMARILLO = "\033[01;33m";
const string BLANCO = "\033[01;37m";
const string ROJO = "\033[22;31m";
const string AZUL = "\033[22;34m";

class Libro:public Publicacion
{
public:
	//Constructores
	//Contructor por defecto
	Libro();
	//Contructor explicito
	void IniciarLibro(long long codigo, string editor, Fecha &fecha, string titulo, string autor);

	//Getters y Setters
	//Para el atributo autor
	string GetAutor() const;
	void SetAutor(string autor);

	//Para el atributo titulo
	string GetTitulo() const;
	void SetTitulo(string titulo);

	//Sobrecarga de operadores
	//Sobrecarga del operador << para poder mostrar los datos de un objeto tipo Revista por pantalla
	friend ostream& operator<<(ostream &out, const Libro &libro);
private:
	string titulo, autor;
};

#endif /* LIBRO_H_ */
