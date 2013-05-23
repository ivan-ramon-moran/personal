#include <iostream>

using namespace std;

#ifndef __LISTA_DINAMICASE__
#define __LISTA_DINAMICASE__

template <class TipoValor>
class ListaDinamicaSE
{
	struct Nodo
	{
		TipoValor info;
		Nodo *sig;
	};

public:
	//Contructor
	ListaDinamicaSE()
	{
		ini = NULL;
		pto = NULL;
		fin = NULL;
	}
	//Destructor
	~ListaDinamicaSE()
	{

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
				ini = nuevo_nodo;
			else
				fin->sig = nuevo_nodo;

			fin = nuevo_nodo;
		}
		else
		{
			*nuevo_nodo = *pto;
			pto->info = objeto;
			pto->sig = nuevo_nodo;

			if (pto == fin)
				fin = nuevo_nodo;

			pto = nuevo_nodo;
		}


		return ok;
	}

	bool Eliminar()
	{
		bool ok = false;
		Nodo *aux;

		//Si el punto esta apuntando a algun punto que no sea NULL
		if (pto != NULL)
		{
			if (pto == ini)
			{
				aux = ini;
				ini = ini->sig;
				delete aux;
				pto = ini;
			}
			else
			{
				if (pto->sig == NULL)
				{
					//Estamos en el ultimo elemento
					//Guardamos el pto en un puntero auxiliar para poder borrarlo luego
					aux = pto;
					//Vamos a inicio
					IrAInicio();

					while (pto->sig != aux)
						pto = pto->sig;

					//Apuntamos el punto de referencia a NULL
					pto->sig = NULL;
					//fin ahora es el pto anterior al que queremos borrar
					fin = pto;
					pto = fin;
					//Borramos el elemento
					delete aux;
				}
				else
				{
					//Estamos en un elemento cualquiera
					//Apuntamos el puntero auxiliar hacia el nodo siguiente
					aux = pto->sig;
					//Copio en el pto actual el valor del pto siguiente
					pto->info = pto->sig->info;
					//Encadeno el pto actual con el siguiente del siguiente, es decir me salto el elemento
					//que realmente vamos a borrar
					pto->sig = pto->sig->sig;
					delete aux;
					pto = pto->sig;
				}
			}

			ok = true;
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

private:
	Nodo *ini, *fin, *pto;
};

#endif
