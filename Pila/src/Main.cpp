//============================================================================
// Name        : Pila.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Pila.cpp"
using namespace std;

int main()
{
	Pila<int> pila;
	Pila<int> pila2;

	pila.Apilar(1);
	pila.Apilar(2);
	pila.Apilar(3);
	pila.Apilar(4);
	pila.Apilar(5);
	pila.Apilar(6);

	pila2.Apilar(7);
	pila2.Apilar(8);

	//Invertirmos la pila
	//pila.ConcatenarPila(pila2);

	//pila.ImprimirPila();
	//pila.ImprimirPila();

	pila.InvertirPila();
	pila.ImprimirPila();
}


