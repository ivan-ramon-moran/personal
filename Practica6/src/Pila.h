#ifndef _PILA_H
#define _PILA_H

#include <iostream>

using namespace std;

class Pila
{
public:
    //Constructor implícito de la clase
    Pila();
    //Metodo para apilar un elemento en la pila.
    bool Apilar (int);
    //Método para desapilar la cima de la pila.
    bool Desapilar ();
    //Método para consultar la cima de la pila.
    bool CimaPila (int &);
    //Método para comprobar si la pila está vacia.
    bool PilaVacia ();
    //Sobrecarga del operador << para poder mostrar la pila por pantalla.
    friend ostream & operator<< (ostream &, const Pila &);

private:
    //Número de elementos de la pila
    static const int MAX = 9;
    //Declaración del array.
    int vector[MAX];
    //declaración de la variable que contiene la posicion de la cima.
    int cima;
};
#endif
