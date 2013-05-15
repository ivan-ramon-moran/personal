#include "Hanoi.h"
#include "Pila.h"
#include <stdlib.h>

/************************************* Hanoi ****************************************
*                                                                                   *
* Prototipo:                                                                        *
*     Hanoi::Hanoi()                                                                *
*                                                                                   *
* Proposito:                                                                        *
*  Constructor de la clase Hanoi                                                    *
*                                                                                   *
* Paramatros:                                                                       *
*  Nombre        Tipo                E/S  Descripcion                               *
*  ------        ----------          ---  ------------                              *
*  No tiene parametros de entrada                                                   *
*                                                                                   *
*  Valor devuelto:                                                                  *
*  Ninguno                                                                          *
************************************************************************************/
Hanoi::Hanoi(){}

/********************************* IniciarJuego *************************************
*                                                                                   *
* Prototipo:                                                                        *
*     void Hanoi::IniciarJuego()                                                    *
*                                                                                   *
* Proposito:                                                                        *
*  Inicia una nueva partida del juego vaciando las pilas por si est�n llenas y      *
*  generando n�meros aleatorios del 1 al 9 para ponererlos en cada una de las pilas *
*  sin que se repita ninguno de ellos en ninguna pila.                              *
*                                                                                   *
* Paramatros:                                                                       *
*  Nombre        Tipo                E/S  Descripcion                               *
*  ------        ----------          ---  ------------                              *
*  No tiene parametros de entrada                                                   *
*                                                                                   *
*  Valor devuelto:                                                                  *
*  Ninguno                                                                          *
************************************************************************************/
void Hanoi::IniciarJuego()
{
    int i, j, num_ale;
    int v[9];
    bool repetido;
    
    //Semilla para generar numeros aleatorios.
    srand(time(NULL));

    //Vaciamos las pilas.
    for(i = 0; i < 3; i++)
    	while (mazos[i].Desapilar());

    //Vaciamos el contador.
    numero_jugadas = 0;
    
    //Creamos un vector con los numeros aleatorios generados
    for (i = 0; i < 9; i++)
    {
    	repetido = false;
    	//Generamos el numero aleatorio entre 1 y 9.
    	num_ale = rand() % 9 + 1;

    	j = 0;
    	//Buscamos si ya existe un elemento con el mismo valor que el numero aleatorio generado.
    	while (j < i && !repetido)
    	{
    		if (v[j] == num_ale)
    			repetido = true;

    		j++;
    	}

    	//Si no existe lo a�adimos, si existe volvemos a iterar con el mismo indice.
    	if (!repetido)
    		v[i] = num_ale;
    	else
    		i--;
    }
    
    //Guardamos en las pilas los numeros generados.
    for(i = 0; i < 3; i++)
    {
        mazos[0].Apilar(v[i]);
		mazos[1].Apilar(v[i+3]);
		mazos[2].Apilar(v[i+6]);
    }
}

/******************************************** MoverCarta ********************************************
*                                                                                                   *
* Prototipo:                                                                                        *
*     bool Hanoi::MoverCarta(int origen, int destino)                                               *
*                                                                                                   *
* Proposito:                                                                                        *
*  Cambiar el elemento de una pila a otra siempre y cuando se cumpla que el elemento de la pila de  *
*  origen es inferior a la cima del mazo de destino.                                                *
*                                                                                                   *
* Paramatros:                                                                                       *
*  Nombre        Tipo                E/S  Descripcion                                               *
*  ------        ----------          ---  ------------                                              *
*  origen        int                  E   Referencia al mazo de origen para hacer el movimiento.    *
*  destino       int                  E   Referencia al mazo de destino para hacer el movimiento.   *
*                                                                                                   *
*  Valor devuelto:                                                                                  *
*        bool hecho.                                                                                *
****************************************************************************************************/
bool Hanoi::MoverCarta(int origen, int destino, int &num_error)
{
    bool hecho = false;
    int valor_ori = 0;
    int valor_dest = 0;
    
    if (!mazos[origen].PilaVacia())
    {
		//Asignamos el valor de la cima de la pila origen.
		mazos[origen].CimaPila(valor_ori);
		//Asignamos el valor de la cima de la pila destino
		mazos[destino].CimaPila(valor_dest);

		//Comprobamos que el origen es menor que el destino
		if (valor_ori < valor_dest || mazos[destino].PilaVacia())
		{
			//Si siguen las reglas, cambiamos la carta de pila.
			mazos[origen].Desapilar();
			mazos[destino].Apilar(valor_ori);
			numero_jugadas++;
			hecho = true;
		}
		else
			//Si el elemento de la pila origen es mayor al de la pila destino, error = 1
			num_error = 1;
    }else
    	// Si la pila origen esta vacia, codificamos el error con 0, para poder mostrarlo.
    	num_error = 0;

    return hecho;
}

/********************************* JuegoFinalizado *************************************
*                                                                                      *
* Prototipo:                                                                           *
*     bool Hanoi::JuegoFinalizado()                                                    *
*                                                                                      *
* Proposito:                                                                           *
*  Comprueba si el juego ha terminado mirando si hay 2 pilas vacias.                   *
*                                                                                      *
* Paramatros:                                                                          *
*  Nombre        Tipo                E/S  Descripcion                                  *
*  ------        ----------          ---  ------------                                 *
*  No tiene parametros de entrada                                                      *
*                                                                                      *
*  Valor devuelto:                                                                     *
*  bool finalizado.-                                                                   *
***************************************************************************************/
bool Hanoi::JuegoFinalizado()
{
    //Inicializamos el boleano a false.
    bool finalizado = false;
    
    //Comprobamos si el mazo 0 y el mazo 1 est�n vacios y,
    //si es as�, cambiamos el boleano.
    if(mazos[0].PilaVacia() && mazos[1].PilaVacia())
        finalizado = true;

    //Comprobamos si el mazo 1 y el mazo 2 est�n vacios y,
    //si es as�, cambiamos el boleano.        
    if(mazos[1].PilaVacia() && mazos[2].PilaVacia())
        finalizado = true;    
        
    //Comprobamos si el mazo 0 y el mazo 2 est�n vacios y,
    //si es as�, cambiamos el boleano.
    if(mazos[0].PilaVacia() && mazos[2].PilaVacia())
        finalizado = true;

    return finalizado;
}

/********************************* ostream& operator<< *********************************
*                                                                                      *
* Prototipo:                                                                           *
*     ostream& operator<< (ostream& out, const Hanoi &hanoi)                           *
*                                                                                      *
* Proposito:                                                                           *
*  Sobrecargamos el operador << para poder mostrar las pilas por pantalla.             *
*                                                                                      *
* Paramatros:                                                                          *
*  Nombre        Tipo                E/S  Descripcion                                  *
*  ------        ----------          ---  ------------                                 *
*  out           ostream             E/S  salida de datos.                             *
*  hanoi         Hanoi               E/S  Objeto de la clase.                          *
*                                                                                      *
*  Valor devuelto:                                                                     *
*  ostream out                                                                         *
***************************************************************************************/
ostream& operator<< (ostream& out, const Hanoi &hanoi)
{
    //Se muestra el n�mero de jugadas
    out << "Numero de jugadas: " << hanoi.numero_jugadas << endl;
    out <<"------------------------------------------------" << endl;
    out << endl;
    //Mostramos el primer mazo o pila.
    out << "Mazo #1: " << hanoi.mazos[0] << endl;
    out << endl;
    //Mostramos el segundo mazo o pila.
    out << "Mazo #2: " << hanoi.mazos[1] << endl;
    out << endl;
    //Mostramos el tercer mazo o pila.
    out << "Mazo #3: " << hanoi.mazos[2]<< endl;
    out << endl;
    out <<"------------------------------------------------" << endl;
    out << endl;
    
    return out;
}
