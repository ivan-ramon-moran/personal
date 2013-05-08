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

	cout << "Elementos: " << cola1.GetNumElementos() << endl;

	while (!cola1.ColaVacia())
	{
		cola1.Desencolar(cad_res);
		cout << "Elementos: " << cola1.GetNumElementos() << endl;
		cout << cad_res << endl;
	}

	cola1.Desencolar(cad_res);

	cola1.Encolar(cad1);

	cola1.Desencolar(cad_res);

	cola1.Desencolar(cad_res);
	cout << cad_res << endl;



	return 0;
}
