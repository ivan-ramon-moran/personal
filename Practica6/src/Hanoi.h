#ifndef _HANOI_H
#define _HANOI_H

#include <iostream>
#include "Pila.h"

using namespace std;

class Hanoi
{
public:
    //Constructor impl�cito de la clase
    Hanoi();
    //M�todo para iniciar un juego.
    void IniciarJuego ();
    //Metodo para cada movimiento de elementos entre pilas.
    bool MoverCarta (int, int, int &num_error);
    //Metodo que comprueba si el juego ha terminado.
    bool JuegoFinalizado ();
    //Sobrecarga del operador <<.
    friend ostream & operator<< (ostream &, const Hanoi &);
private:
    //Constante para el numero de pilas del vector de pilas.
    static const int MAX_PILAS = 3;
    //Contador de jugadas.
    int numero_jugadas;
    //Declaraci�n de un vector de tipo pilas.
    typedef Pila VectorMazos[MAX_PILAS];
    //Declaracion del vector.
    VectorMazos mazos;
};

#endif
