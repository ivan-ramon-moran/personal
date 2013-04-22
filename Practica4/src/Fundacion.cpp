#include "Fundacion.h"

//Constructores
//Contructor por defecto
Fundacion::Fundacion(){}

//Contructor explicito
Fundacion::Fundacion(string nombre, float saldo)
{
	//Asignamos el nombre de la fundacion y el saldo.
	SetNombreFundacion(nombre);
	SetSaldo(saldo);

	//Asignamos tambien al campo presidente una cadena por defecto que indique que no hay presidente.
	presidente = "Sin presidente...";
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
	int posicion;

	//Miramos si existe el miembro en la lista de mimbros
	posicion = BuscarMiembro(dni);

	if (posicion != -1)
	{
		//Si existe, añadimos el presidente
		this->presidente = dni;
		es_miembro = true;
	}

	//Si no existe no hacemos nada
	return es_miembro;
}

bool Fundacion::IngresarDinero(float cantidad)
{
	bool ok = false;

	//Si la cantidad es positiva la ingresamos, si es negativa no hacemos nada.
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

	//Si tenemos más saldo del que queremos retirar, permitimos la operacion, si no no hacemos nada.
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

	//Siempre y cuando el miembro no esta ya en la lista, permitimos la operacion.
	posicion = BuscarMiembro(p.GetDNI());

	if (posicion == -1)
	{
		miembros.push_back(p);
		ok = true;
	}

	return ok;
}

int Fundacion::BuscarMiembro(string dni)
{
	int posicion = -1;

	//Busacamos si existe un miembro con el mismo dni que le pasamos a la funcion como parametro.
	for (int i = 0; i < miembros.size(); i++)
		if (miembros[i].GetDNI() == dni)
			posicion = i;

	//devolvemos -1 si no existe ningun miembro con el dni buscado, o el indice si si que existe.

	return posicion;
}

bool Fundacion::DesligarMiembro(string dni)
{
	bool ok = false;
	int posicion;

	//Buscamos el miembro, ya que no tiene sentido desligar a un miebro que no exista en la lista.
	posicion = BuscarMiembro(dni);

	if (posicion != -1)
	{
		//En el caso de que exista el miembro en el vector
		//Comprobamos si es el presidente, si lo es ponemos a la fundacion que no tiene presidente.
		if (miembros[posicion].GetNombre() == GetNombrePresidente())
			SetNombrePresidente("La fundacion no tiene presidente");

		//Eliminamos la persona del vector
		miembros[posicion] = miembros.back();
		miembros.pop_back();
		ok = true;
	}

	return ok;
}

//Sobrecargas de operadores

bool Fundacion::operator+(int cantidad)
{
	//Sobrecarga del operador + que nos permite ingresar dinero de la forma f + 200;
	bool ok;

	ok = IngresarDinero(cantidad);

	return ok;
}

bool Fundacion::operator-(int cantidad)
{
	//Sobrecarga del operador - que nos permite retirar dinero de la forma f - 200;
	bool ok;

	ok = RetirarDinero(cantidad);

	return ok;
}

bool Fundacion::operator+(Persona &p)
{
	//Sobrecarga del operador + que nos permite añadir un miebro de la forma f + persona;
	bool ok;

	ok = AgregarMiembro(p);

	return ok;
}

bool Fundacion::operator-(string dni)
{
	//Sobrecarga del operador - que nos permite quitar un miebro de la forma f - persona;
	bool ok;

	ok = DesligarMiembro(dni);

	return ok;
}

ostream& operator<< (ostream &out, Fundacion &f)
{
	/*Sobrecarga del operador de flujo de salida que nos permite imprimir los datos de una fundacion
	de la forma cout << fundacion;*/
	int indice = f.BuscarMiembro(f.presidente);

	out << "----------------------------------------------" << endl;
	out << "            DATOS DE LA FUNDACION             " << endl;
	out << "----------------------------------------------" << endl;


	if (indice != -1)
	{
		Persona p = f.miembros[indice];

		out << endl << "Nombre: " << f.nombre << endl << "Presidente: " << p.GetNombre() << " " << p.GetApellido1() << " " << p.GetApellido2() << endl << "saldo: " << f.saldo << " €" << endl;
	}
	else
	{
		out << endl << "Nombre: " << f.nombre << endl << "Presidente: " << f.presidente << endl << "saldo: " << f.saldo << " €" << endl;
	}
}

void Fundacion::ImprimirLista()
{
	/*Funcion que nos permite imprimir una lista de miembros mediante la sobrecaga definida en la
	clase Persona.cpp de la forma cout << persona;*/
	cout << "--------------------------------------------" << endl;
	cout << "              LISTA MIEMBROS                " << endl;
	cout << "--------------------------------------------" << endl;

	//Recorremos con un for la lista de miembros y imprimimos sus datos.
	for (unsigned int i = 0; i < miembros.size(); i++)
	{
		cout << endl << "Miembro: " << i << endl;
		cout << miembros[i] << endl;
	}
}
