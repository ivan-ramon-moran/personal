#include "Archivo.h"

Archivo::Archivo() {}

Archivo::Archivo(string nombre, string ruta, string tipo, unsigned long long tamanyo)
{
	this->nombre = nombre;
	this->ruta = ruta;
	this->tipo = tipo;
	this->tamanyo = tamanyo;
}

string Archivo::get_nombre()
{
	return this->nombre;
}

void Archivo::set_nombre(string nombre)
{
	this->nombre = nombre;
}

string Archivo::get_ruta()
{
	return this->ruta;
}

void Archivo::set_ruta(string ruta)
{
	this->ruta = ruta;
}

string Archivo::get_tipo()
{
	return this->tipo;
}

void Archivo::set_tipo(string tipo)
{
	this->tipo = tipo;
}

unsigned long long Archivo::get_tamanyo()
{
	return this->tamanyo;
}

void Archivo::set_tamanyo(unsigned long long tamanyo)
{
	this->tamanyo = tamanyo;
}
