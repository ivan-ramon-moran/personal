#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

using namespace std;

template <class Tipo>

class Vector
{

public:
    Vector(int tamanyo)
	{
		this->elementos_actuales = 0;
		this->tamanyo = tamanyo;
		ptrVector = new Tipo[tamanyo];
	}
	
	void add(const Tipo &objeto)
	{
		ptrVector[this->elementos_actuales] = objeto;
		elementos_actuales++;
	
		if (elementos_actuales == tamanyo)
		{
			cout << "Redimensionando el vector de " << this->tamanyo << " a " << this->tamanyo + this->tamanyo << endl;   
			Tipo *ptrVectorAux = new Tipo[this->tamanyo + tamanyo];
		
		
			for (int i = 0; i < tamanyo; i++)
			{
				ptrVectorAux[i] = ptrVector[i];
			}
		
			this->tamanyo += tamanyo;
		
			delete [] ptrVector;
		
			ptrVector = ptrVectorAux;	
		}
	}
	
	Tipo& get(int indice) const
	{
		return this->ptrVector[indice];
	}

private:
	int tamanyo;
	Tipo *ptrVector;
	int elementos_actuales;
};

#endif // VECTOR_H
