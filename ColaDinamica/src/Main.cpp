/* Estructura de datos Cola con administracion de memoria dinámica */

#include <iostream>
#include "ColaDinamica.cpp"
using namespace std;

int main()
{
	ColaDinamica<string> cola1;

	string cad1 = "Hola";
	string cad2 = "Me";
	string cad3 = "LLamo";
	string cad4 = "Ivan";
	string cad_res;

	cola1.Encolar(cad1);
	cola1.Encolar(cad2);
	cola1.Encolar(cad3);
	cola1.Encolar(cad4);

	cola1.MostrarCola();



	return 0;
}
