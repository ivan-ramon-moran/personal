#include <iostream>

using namespace std;

template <class TipoValor>
class ColaDinamica
{
	struct Nodo
	{
		TipoValor objeto;
		Nodo *sig;
	};

public:
	ColaDinamica()
	{
		//Fin e inicio a NULL
		num_elementos = 0;
		inicio = NULL;
		fin = NULL;
	}

	bool ColaVacia()
	{
		//En el momento que inicio sea igual a NULL quiere decir que la pila esta vacia
		return (inicio == NULL);
	}

	bool Encolar(TipoValor &valor)
	{
		bool ok = false;
		//Creamos un nuevo nodo
		Nodo *nodo = new Nodo;
		//Asignamos al nuevo nodo el valor que queremos encolar
		nodo->objeto = valor;

		if (inicio == NULL)
		{
			//Si la cola esta vacia, asignamos el elemento a inicio, ya que es el nodo inicial
			inicio = nodo;
			fin = inicio;
		}
		else
		{
			//Si la cola no esta vacia, lo asignamos a nuestro puntero fin.
			fin->sig = nodo;
			fin = fin->sig;
		}

		ok = true;
		//Incrementamos en uno el numero de elementos que tiene la lista
		num_elementos++;

		return ok;
	}

	bool Desencolar(TipoValor &valor)
	{
		bool ok = true;
		//Nodo auxiliar para eliminar el nodo anterior.
		Nodo *nodo_aux = inicio;

		//Mientras que la pila no este vacia desencolamos
		if (!ColaVacia())
		{
			valor = inicio->objeto;
			inicio = inicio->sig;

			if (inicio == NULL)
				fin = NULL;

			//Eliminamos el nodo que apuntaba a inicio
			delete nodo_aux;
			num_elementos--;
		}
		else
			ok = false;

		return ok;
	}

	int GetNumElementos()
	{
		return this->num_elementos;
	}
private:
	Nodo *inicio, *fin;
	int num_elementos;
};


