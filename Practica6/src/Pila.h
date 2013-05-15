#ifndef _PILA_H
#define _PILA_H

#include <iostream>

using namespace std;

class Pila
{
public:
    //Constructor impl�cito de la clase
    Pila();
    //Metodo para apilar un elemento en la pila.
    bool Apilar (int);
    //M�todo para desapilar la cima de la pila.
    bool Desapilar ();
    //M�todo para consultar la cima de la pila.
    bool CimaPila (int &);
    //M�todo para comprobar si la pila est� vacia.
    bool PilaVacia ();
    //Sobrecarga del operador << para poder mostrar la pila por pantalla.
    friend ostream & operator<< (ostream &, const Pila &);

private:
    //N�mero de elementos de la pila
    static const int MAX = 9;
    //Declaraci�n del array.
    int vector[MAX];
    //declaraci�n de la variable que contiene la posicion de la cima.
    int cima;
};
#endif
