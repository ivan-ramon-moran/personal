#include <iostream>

using namespace std;

#ifndef ARCHIVO_H_
#define ARCHIVO_H_

class Archivo
{
public:
	Archivo();
	Archivo(string nombre, string ruta, string tipo, unsigned long long tamanyo);

	string get_nombre();
	void set_nombre(string nombre);

	string get_ruta();
	void set_ruta(string ruta);

	string get_tipo();
	void set_tipo(string tipo);

	unsigned long long get_tamanyo();
	void set_tamanyo(unsigned long long tamanyo);

private:
	string nombre;
	string ruta;
	string tipo;
	unsigned long long tamanyo;
};

#endif /* ARCHIVO_H_ */
