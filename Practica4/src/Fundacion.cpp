#include "Fundacion.h"

//Constructores
//Contructor por defecto
Fundacion::Fundacion()
{

}

//Contructor explicito
Fundacion::Fundacion(string nombre, float saldo)
{
	SetNombreFundacion(nombre);
	SetSaldo(saldo);
}

//getters y setters
string Fundacion::GetNombreFundacion()
{
	return this->nombre;
}

void Fundacion::SetNombreFundacion(string nombre)
{
	this->nombre = nombre;
}

float Fundacion::GetSaldo()
{
	return this->saldo;
}

void Fundacion::SetSaldo(float saldo)
{
	this->saldo = saldo;
}

string Fundacion::GetNombrePresidente()
{
	return this->nombre;
}

bool Fundacion::SetNombrePresidente(string dni)
{
	bool es_miembro = false;

	this->presidente = dni;

	return es_miembro;
}

bool Fundacion::IngresarDinero(float cantidad)
{
	bool ok = false;

	if (cantidad > 0)
	{
		this->saldo += cantidad;
		ok = true;
	}

	return ok;
}

bool Fundacion::RetirarDinero(float cantidad)
{
	bool ok = false;

	if (this->saldo > cantidad && cantidad > 0)
	{
		this->saldo -= cantidad;
		ok = true;
	}

	return ok;
}

bool Fundacion::AgregarMiembro(Persona &p)
{
	bool ok = false;
	int posicion;

	posicion = BuscarMiembro(p.GetDNI());

	if (posicion == -1)
	{
		miembros.insert(miembros.begin(), p);
		ok = true;
	}

	return ok;
}

int Fundacion::BuscarMiembro(string dni)
{
	int posicion = -1;

	for (int i = 0; i < miembros.size(); i++)
		if (miembros[i].GetDNI() == dni)
			posicion = i;

	return posicion;
}

bool Fundacion::DesligarMiembro(string dni)
{
	bool ok = false;
	int posicion;

	posicion = BuscarMiembro(dni);

	if (posicion != -1)
	{
		//Comprobamos si es el presidente
		if (miembros[posicion].GetNombre() == GetNombrePresidente())
			SetNombrePresidente("La fundacion no tiene presidente");

		miembros[posicion] = miembros.back();
		miembros.pop_back();
		ok = true;
	}

	return ok;
}

//Sobrecargas de operadores

bool Fundacion::operator+(int cantidad)
{
	bool ok;

	ok = IngresarDinero(cantidad);

	return ok;
}

bool Fundacion::operator-(int cantidad)
{
	bool ok;

	ok = RetirarDinero(cantidad);

	return ok;
}

bool Fundacion::operator+(Persona &p)
{
	bool ok;

	ok = AgregarMiembro(p);

	return ok;
}

bool Fundacion::operator-(string dni)
{
	bool ok;

	ok = DesligarMiembro(dni);

	return ok;
}
