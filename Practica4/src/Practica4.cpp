//============================================================================
// Name        : Practica4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Persona.h"
#include "Fundacion.h"

using namespace std;

const int SALIDA_PROGRAMA = 7;
const string OPE_OK = "[OK] La operacion se ha realizado correctamente.";
const string OPE_FAIL = "[ERROR] No se ha podido realizar la operacion.";

int MostrarMenu();
void Menu(Fundacion &f);
bool AgregarMiembro(Fundacion &f);

int main()
{
	//Persona p("176223","Jorge", "Salguero", "Dominguez");
	Fundacion f("Voos", 0);

	Menu(f);


	return 0;
}

int MostrarMenu()
{
	int opcion;


	cout << "\n" << "[1].Cambiar nombre." << "\n" << "[2].Ingresar dinero." << "\n"
		<< "[3].Retirar dinero." << "\n" << "[4].Cambiar presidente." << "\n" << "[5].Agregar miembro." << "\n"
		<< "[6].Desligar miembro" << "\n" << "[7].Salir" << endl;
	cout << "Introduce una opcion:" ;
	cin >> opcion;

	return opcion;
}

void Menu(Fundacion &f)
{
	int opcion = -1;
	string nombre_f, dni;
	float cantidad;
	bool operacion_realizada;


	while (opcion != SALIDA_PROGRAMA)
	{
		opcion = MostrarMenu();

		switch(opcion)
		{
			case 1:
				cout << "Introduce el nuevo nombre de la fundacion: ";
				cin >> nombre_f;
				f.SetNombreFundacion(nombre_f);
				cout << OPE_OK << endl;
				break;
			case 2:
				cout << "Introduce la cantidad de dinero que quieres ingresar: ";
				cin >> cantidad;

				operacion_realizada = f + cantidad;

				if (operacion_realizada)
					cout << OPE_OK << " Su nuevo saldo es: " << f.GetSaldo() << endl;
				else
					cout << OPE_FAIL << endl;

				break;
			case 3:
				cout << "Introduce la cantidad de dinero que quieres retirar: ";
				cin >> cantidad;

				operacion_realizada = f.RetirarDinero(cantidad);

				if (operacion_realizada)
					cout << OPE_OK << " Su nuevo saldo es: " << f.GetSaldo() << endl;
				else
					cout << OPE_FAIL << endl;

				break;
			case 4:
				cout << "Introduce el dni del nuevo presidente: ";
				cin >> dni;
				operacion_realizada = f.SetNombrePresidente(dni);

				if (operacion_realizada)
					cout << OPE_OK << endl;
				else
					cout << OPE_FAIL << endl;

				break;
			case 5:
				operacion_realizada = AgregarMiembro(f);

				if (operacion_realizada)
					cout << OPE_OK << endl;
				else
					cout << OPE_FAIL << endl;

				break;
			case 6:
				cout << "Introduce el DNI de la persona: ";
				cin >> dni;

				operacion_realizada = f - dni;

				if (operacion_realizada)
					cout << OPE_OK << endl;
				else
					cout << OPE_FAIL << endl;

				break;
		}
	}
}

bool AgregarMiembro(Fundacion &f)
{
	string nombre, apellido1, apellido2, dni;
	bool res_ope;

	cout << "Introduce el DNI: ";
	cin >> dni;

	cout << "Introduce el nombre ";
	cin >> nombre;

	cout << "Introduce el primer apellido ";
	cin >> apellido1;

	cout << "Introduce el segundo apellido ";
	cin >> apellido2;

	Persona p(dni, nombre, apellido1, apellido2);
	res_ope = f + p;

	return res_ope;
}
