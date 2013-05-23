#include <iostream>

using namespace std;

#ifndef __LISTA_DINAMICA__DENC__
#define	__LISTA_DINAMICA__DENC__

template <class TipoValor>
class ListaDinamicaDENC
{
	struct Nodo
	{
		Nodo *sig, *ant;
		TipoValor info;
	};

public:
	ListaDinamicaDENC()
	{
		cab = new Nodo;
		cab->ant = cab;
		cab->sig = cab;
		pto = cab;
	}
	~ListaDinamicaDENC()
	{

	}

	ListaDinamicaDENC(const ListaDinamicaDENC &lista)
	{
		Nodo *nodo_copia, *nodo_aux;

		cab = new Nodo();
		cab->ant = cab;
		cab->sig = cab;
		pto = cab;

		nodo_aux = lista.cab->sig;

		while (nodo_aux != lista.cab)
		{
			nodo_copia = new Nodo;
			nodo_copia->info = nodo_aux->info;
			nodo_copia->sig = pto;
			nodo_copia->ant = pto->ant;
			pto->ant->sig = nodo_copia;
			pto->ant = nodo_copia;

			nodo_aux = nodo_aux->sig;
		}
	}

	bool ListaVacia()
	{
		return (cab->sig == cab);
	}

	bool FinalLista()
	{
		return (pto->sig == cab);
	}

	bool Avanzar()
	{
		bool ok = false;

		if (pto != cab)
		{
			pto = pto->sig;
			ok = true;
		}

		return ok;
	}

	bool Consultar(TipoValor &valor)
	{
		bool ok = false;

		if (pto != cab)
		{
			valor = pto->info;
			ok = true;
		}

		return ok;
	}

	bool Insertar(TipoValor &valor)
	{
		bool ok = false;
		Nodo *nodo_nuevo;

		nodo_nuevo = new Nodo;
		nodo_nuevo->info = valor;
		nodo_nuevo->sig = pto;
		nodo_nuevo->ant = pto->ant;
		pto->ant->sig = nodo_nuevo;
		pto->ant = nodo_nuevo;

		ok = true;

		return ok;
	}

	void MostrarLista()
	{
		Nodo *nodo_aux = cab->sig;

		while (nodo_aux != cab)
		{
			cout << nodo_aux->info << " ";
			nodo_aux = nodo_aux->sig;
		}
	}

	bool Eliminar()
	{
		bool ok = false;
		Nodo *nodo_aux = pto;

		if (cab->sig != cab)
		{
			pto->ant->sig = pto->sig;
			pto->sig->ant = pto->ant->sig;
			pto = pto->sig;
			delete nodo_aux;
			ok = true;
		}

		return ok;
	}

	void IrAInicio()
	{
		pto = cab->sig;
	}

private:
	Nodo *cab, *pto;
};

#endif
