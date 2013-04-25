#include "Excepcion.cpp"
#include <iostream>
#include <exception>

using namespace std;

double Dividir(int numero1, int numero2);
void Funcion1();
void Funcion2();
void Funcion3();

int main()
{

	//Intentamos dividir por 0 y capturamos la excepcion.

	try
	{
		cout << Dividir(7,0);
	}
	catch (Excepcion &divideByZeroException)
	{
		cout << "Ocurrio una excepcion: " << divideByZeroException.what() << endl;
	}

	try
	{
		Funcion1();
	}
	catch (runtime_error &error)
	{
		cout << "Ocurrio una excepcion manejada por el main: " << error.what() << endl;
	}

	return 0;
}

double Dividir(int numero1, int numero2)
{
	double resultado;

	//Podemos atrapar la eccepcion en esta funcion y procesarla en el main declarando otro bloque try, catch
	try
	{
		if (numero2 != 0)
			resultado = double(numero1) / numero2;
		else
			throw Excepcion();
	}
	catch (Excepcion &divideByZeroException)
	{
		throw; //Al poner throw de nuevo nos vamos al le pasamos el control al try del main.
	}

	return resultado;
}

void Funcion3()
{
	cout << "En la funcion 3" << endl;
	//Ejemplo de propagacion de una excepcion hasta el main.
	throw runtime_error("Error en la funcion 3");
}

void Funcion2()
{
	Funcion3();
}


void Funcion1()
{
	Funcion2();
}



