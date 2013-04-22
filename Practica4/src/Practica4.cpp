//includes
#include <iostream>
#include "Persona.h"
#include "Fundacion.h"

using namespace std;

//Contantes del programa (salida del programa y mensajes de estado)
const int SALIDA_PROGRAMA = 7;
const string OPE_OK = "[OK] La operacion se ha realizado correctamente.";
const string OPE_FAIL = "[ERROR] No se ha podido realizar la operacion.";

//Prototipos
int MostrarMenu();
void Menu(Fundacion &f);
bool AgregarMiembro(Fundacion &f);

int main()
{
	//Creamos una fundacion con nombre "Voos" y saldo 0.
	Fundacion f("Voos", 0);

	//Iniciamos el programa mostrando el menu de opciones que tiene el usuario.
	Menu(f);

	return 0;
}

int MostrarMenu()
{
	int opcion;

	//Mostramos el menu
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
		//Imprimimos el menu y pedimos al usuario una opcion.
		opcion = MostrarMenu();

		switch(opcion)
		{
			case 1:
				//El case 1 corresponde a la opcion de cambiar el nombre de la fundación.
				//Leemos y almacenamos el nuevo nombre
				cout << "Introduce el nuevo nombre de la fundacion: ";
				cin >> nombre_f;
				//Asiganamos el nuevo nombre
				f.SetNombreFundacion(nombre_f);
				//Imprimimos un mensaje indicado el resultado de la operacion
				cout << OPE_OK << endl;
				//Mostramos los datos de la fundacion.
				cout << f << endl;
				break;
			case 2:
				//El case 2 corresponde a la opcion de ingresar dinero en la fundacion
				//Leemos y almacenamos la cantidad que vamos a ingresar en la fundacion.
				cout << "Introduce la cantidad de dinero que quieres ingresar: ";
				cin >> cantidad;

				//Ingresamos el dinero y obtenemos el resultado de la operacion.
				operacion_realizada = f + cantidad;

				//Dependiendo del resultado de la operacion, mostramos un mensaje.
				if (operacion_realizada)
					cout << OPE_OK << " Su nuevo saldo es: " << f.GetSaldo() << endl;
				else
					cout << OPE_FAIL << endl;

				//Imprimimos los nuevos datos de la fundacion.
				cout << f << endl;
				break;
			case 3:
				//El case 3 corresponde a la opcion de retirar dinero de la fundacion.
				//Leemos y almacenamos la cantidad que vamos a retirar en la fundacion.
				cout << "Introduce la cantidad de dinero que quieres retirar: ";
				cin >> cantidad;

				//Retiramos el dinero y obtenemos el resultado de la operacion.
				operacion_realizada = f.RetirarDinero(cantidad);

				//Dependiendo del resultado de la operacion, mostramos un mensaje.
				if (operacion_realizada)
					cout << OPE_OK << " Su nuevo saldo es: " << f.GetSaldo() << endl;
				else
					cout << OPE_FAIL << endl;

				//Mostramos los datos actualizados de la fundacion.
				cout << f << endl;
				break;
			case 4:
				//El case 4 se corresponde a la opcion de cambiar de presidente por el dni
				//Leemos y almacenamos el DNI.
				cout << "Introduce el dni del nuevo presidente: ";
				cin >> dni;

				//Realizamos la operacion y guardamos el resultado
				operacion_realizada = f.SetNombrePresidente(dni);

				//Dependiendo del resultado mostramos un mensaje.
				if (operacion_realizada)
					cout << OPE_OK << endl;
				else
					cout << OPE_FAIL << endl;

				//Mostramos los datos actualizados de la fundacion.
				cout << f;

				break;
			case 5:
				//El case 5 corresponde a la opcion de agregar un nuevo miembro
				/*Llamamos a la funcion AgregarMiembro(f) que lo que hace es leer una persona
				y añadirla en la lista de miembros, tambien guardamos el resultado de la operacion.*/
				operacion_realizada = AgregarMiembro(f);

				//Dependiendo del resultado de la operacion mostramos un mensaje
				if (operacion_realizada)
					cout << OPE_OK << endl;
				else
					cout << OPE_FAIL << endl;

				//Imprimimos la lista de miembros.
				f.ImprimirLista();

				break;
			case 6:
				//El case 6 se corresponde a la pocion de borrar un miembro de la lista
				//Leemos y alamcenamos el DNI
				cout << "Introduce el DNI de la persona: ";
				cin >> dni;

				//Realizamos la operacion y guardamos el resultado de la misma
				operacion_realizada = f - dni;

				//Dependiendo del resultado mostramos un mensaje
				if (operacion_realizada)
					cout << OPE_OK << endl;
				else
					cout << OPE_FAIL << endl;

				//Imprimimos la lista de miembros modificada
				f.ImprimirLista();

				break;
		}
	}
}

bool AgregarMiembro(Fundacion &f)
{
	string nombre, apellido1, apellido2, dni;
	bool res_ope;

	//Leemos los atributos y cremos una nueva persona.
	cout << "Introduce el DNI: ";
	cin >> dni;

	cout << "Introduce el nombre ";
	cin >> nombre;

	cout << "Introduce el primer apellido ";
	cin >> apellido1;

	cout << "Introduce el segundo apellido ";
	cin >> apellido2;

	Persona p(dni, nombre, apellido1, apellido2);
	//Añadimos la persona a la lista de miembros.
	res_ope = f + p;

	return res_ope;
}
