/*
 * Pila.h
 *
 *  Created on: 20/04/2013
 *      Author: k3rnel
 */

#ifndef PILA_H_
#define PILA_H_

#include <iostream>
#include <vector>

using namespace std;

template <class Tipo>

class Pila
{
	struct Nodo
	{
		//Objeto o valor si es un tipo simple que almacenara la pila.
		Tipo objeto;
		//Puntero que enlaza un nodo con el siguiente.
		Nodo *sig;
	};

public:
	//Contructor
	Pila()
	{
		//Asignamos cima a NULL ya que la pila no contiene objetos!!!
		cima = NULL;
		num_elementos = 0;
	}

	//Funcion que permite añadir un objeto a la pila.
	void Apilar(Tipo objeto)
	{
		//Creamos un nuevo nodo, que contendra el valor que queremos apilar.
		Nodo *nuevo_nodo = new Nodo;

		//Asignamos el valor al nuevo nodo.
		nuevo_nodo->objeto = objeto;
		//Enlazamos el nuevo nodo con el nodo que esta por debajo.
		nuevo_nodo->sig = cima;
		//Posicionamos la cima en el nuevo nodo.
		cima = nuevo_nodo;
		num_elementos++;
	}

	//Funcion que permite desapilar un elemento en la pila.
	bool Desapilar()
	{
		bool ok = false;

		if (cima != NULL)
		{	//Creamos un nodo auxiliar.
			Nodo *nodo_aux = new Nodo;

			//Apuntamos el nodo auxiliar a la cima.
			nodo_aux = cima;
			//La cima ahora apunta al objeto que tiene por debajo
			cima = cima->sig;
			//Borramos el objeto que esta por encima de la pila ahora.
			delete nodo_aux;
			num_elementos--;
			ok = true;
		}

		return ok;
	}

	//Funcion que permite obtener el elemento que esta en la cima.
	bool ObtenerValor(Tipo &objeto)
	{
		bool ok = false;

		if (cima != NULL)
		{	//Devuelve el objeto actual en la cima de la pila.
			objeto = cima->objeto;
			ok = true;
		}

		return ok;
	}

	bool PilaVacia()
	{
		bool esta_vacia = false;

		if (cima == NULL)
			esta_vacia = true;

		return esta_vacia;
	}

	int GetNumeroElementos()
	{
		return this->num_elementos;
	}

	void ConcatenarPila(const Pila &p)
	{
		Nodo * cimap1_aux = cima;
		Nodo * cimap2_aux = p.cima;

		//Situamos la cima auxilar en el ultimo ultimo/primer (depende de como se mire) de la pila
		while (cimap1_aux->sig != NULL)
		{
			cimap1_aux = cimap1_aux->sig;
		}

		//Recorremos la pila 2 y vamos concatenando los nodos de la pila2 a la pila 1
		while (cimap2_aux != NULL)
		{
			//Concateno el nodo
			cimap1_aux->sig = cimap2_aux;

			//Avanzo al siguiente nodo en las 2 pilas
			cimap2_aux = cimap2_aux->sig;
			cimap1_aux = cimap1_aux->sig;
		}
	}

	void ImprimirPila()
	{
		Nodo *cima_aux = cima;

		while (cima_aux != NULL)
		{
			cout << cima_aux->objeto;
			cima_aux = cima_aux->sig;
		}
	}

	void InvertirPila()
	{
		vector<Tipo> v;
		Nodo *cima_aux = cima;

		while (cima_aux != NULL)
		{
			//Metemos el elemento en el vector
			v.push_back(cima_aux->objeto);
			cima_aux = cima_aux->sig;
		}

		cima_aux = cima;

		for (int i = v.size() - 1; i >= 0; i--)
		{
			cima_aux->objeto = v[i];
			cima_aux = cima_aux->sig;
		}
	}

private:
	//Puntero de tipo nodo que apunta hacia la cima de la pila.
	Nodo *cima;
	//Numero de elementos actuales en la pila
	int num_elementos;
};

#endif /* PILA_H_ */
