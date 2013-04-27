
#ifndef _FECHA_H
#define _FECHA_H

#include <iostream>
using namespace std;

class Fecha
{
public:
	Fecha ();

	Fecha IniciarFecha (int d, int m, int a);

	friend ostream& operator<< (ostream & out, const Fecha &fec);
	friend istream& operator>> (istream & in, Fecha & f);

	//Sobrecarga de operadores
	//Como metodo de clase
	bool operator>(Fecha &fecha);
	bool operator< (Fecha &fecha);

	void ImprimirFecha();

private:
	int dia;
	int mes;
	int anyo;
	int Fecha2Int ();
};

#endif
