#include "ListaDinamicaDENC.cpp"
#include <iostream>

using namespace std;

int main()
{
	ListaDinamicaDENC<int> lista;

	int a,b,c,d,e,f, consulta;

	a = 1;
	b = 2;
	c = 3;
	d = 4;
	e = 5;
	f = 6;

	lista.Insertar(a);
	lista.Insertar(b);
	lista.Insertar(c);
	lista.Insertar(d);
	lista.Insertar(e);
	lista.Insertar(f);

	lista.IrAInicio();
	ListaDinamicaDENC<int> copia(lista);
	lista.Eliminar();

	lista.MostrarLista();
	cout << endl;
	copia.MostrarLista();

	return 0;
}
