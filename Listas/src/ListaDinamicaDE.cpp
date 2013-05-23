#include <iostream>

using namespace std;

#ifndef __LISTA_DINAMICADE__
#define __LISTA_DINAMICADE__

template <class TipoValor>
class ListaDinamicaDE
{
	struct Nodo
	{
		TipoValor info;
		Nodo *sig;
		Nodo *ant;
	};

public:
	//Contructor
	ListaDinamicaDE()
	{
		ini = NULL;
		pto = NULL;
		fin = NULL;
	}
	//Destructor
	~ListaDinamicaDE()
	{

	}

	ListaDinamicaDE(const ListaDinamicaDE &lista)
	{
		Nodo *nodo_copia, *nodo_aux;

		fin = NULL;
		pto = NULL;
		ini = NULL;
		nodo_aux = lista.ini;

		while (nodo_aux != NULL)
		{
			nodo_copia = new Nodo;
			nodo_copia->info = nodo_aux->info;
			nodo_copia->sig = NULL;

			if (ini == NULL)
			{
				ini = nodo_copia;
				nodo_copia->ant = NULL;
			}
			else
			{
				nodo_copia->ant = fin;
				fin->sig = nodo_copia;
			}

			fin = nodo_copia;
			nodo_aux = nodo_aux->sig;
		}

	}

	//Operaciones permitidas
	bool Insertar(TipoValor &objeto)
	{
		bool ok = false;
		Nodo *nuevo_nodo;

		nuevo_nodo = new Nodo;

		if (pto == NULL)
		{
			nuevo_nodo->info = objeto;
			nuevo_nodo->sig = NULL;

			if (ini == NULL)
			{
				ini = nuevo_nodo;
				nuevo_nodo->ant = NULL;
			}
			else
			{
				nuevo_nodo->ant = fin;
				fin->sig = nuevo_nodo;
			}

			fin = nuevo_nodo;
		}
		else
		{
			nuevo_nodo->info = objeto;
			nuevo_nodo->sig = pto;
			nuevo_nodo->ant = pto->ant;
		}

		return ok;
	}

	bool Eliminar()
	{
		bool ok = false;
		Nodo *aux;

		if (pto != NULL)
		{
			if (pto == ini)
			{
				aux = ini;
				ini = ini->sig;
				delete aux;
			}
			else
			{
				aux = pto;
				pto->ant->sig = pto->sig;
				pto = pto->sig;
				delete aux;
			}
		}

		return ok;
	}

	bool Consultar(TipoValor &objeto)
	{
		bool ok = false;

		//Si el punto de interes apunta a algun elemento con contenido no NULL!!!
		if (pto != NULL)
		{
			objeto = pto->info;
			ok = true;
		}

		return ok;
	}

	void IrAInicio()
	{
		pto = ini;
	}

	bool FinalLista()
	{
		return (pto == NULL);
	}

	bool ListaVacia()
	{
		return (ini == NULL);
	}

	bool Avanzar()
	{
		bool ok = false;

		if (pto != NULL)
		{
			pto = pto->sig;
			ok = true;
		}

		return ok;
	}

	void MostrarLista()
	{
		IrAInicio();
		TipoValor valor;

		while (!FinalLista())
		{
			Consultar(valor);
			Avanzar();
			cout << valor << " ";
		}
	}

private:
	Nodo *ini, *fin, *pto;
};

#endif





