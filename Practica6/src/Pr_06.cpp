/***************************** Pr�ctica 6 -- Hanoi ******************************************
*                                                                                           *
*    PR�CTICA 6, CLASES PILA Y HANOI.                                                       *
*    PROP�SITO: Implementar las clases Pila y Hanoi para desarrollar el juego.              *
*                                                                                           *
*    Autores: Iv�n Ram�n Mor�n y Jorge Salguero Dom�nguez                                   *
*                                                                                           *
********************************************************************************************/
#include <iostream>
#include "Hanoi.h"
#include "Pila.h"

//Funciones del programa principal
void Reglas ();
bool Movimiento(Hanoi &hanoi, int &num_error);

using namespace std;
/******************************************************************************************/
/************************           Programa principal             ************************/
/******************************************************************************************/
int main ()
{
    setlocale(LC_ALL, "spanish");
    
    Hanoi hanoi;
    char comenzar;
    int num_error;
    
    cout << "-------------- BIENVENIDO A HANOI --------------" << endl;
    comenzar = 's';
    
    while (comenzar == 's')
    {
    	//Mostramos las reglas por pantalla
        Reglas();
        //Iniciamos el juego
        hanoi.IniciarJuego();
    
        //Mientras no este terminado, pedimos movimientos
        while(!hanoi.JuegoFinalizado())
        {
            //Mostramos las pilas
            cout << hanoi << endl;
            
            //Leemos el movimiento y si no es correcto, se muestra el mensaje de error
            if (!Movimiento(hanoi, num_error))
            {
                cout << endl;
                cout << "***********************************************************************" << endl;
                cout << ">>>>>>>>>>>>>>>>>>>>> !! MOVIMIENTO INCORRECTO !! <<<<<<<<<<<<<<<<<<<<<" << endl;
                cout << "***********************************************************************" << endl;

                if (num_error == 0)
                	cout << "La jugada no se ha podido realizar porque la pila origen seleccionada\n"
                		 << "esta vacia. Selecciona una pila origen que contenga elementos." << endl;
                else if(num_error == 1)
                	cout << "La jugada no se ha podido realizar porque el elemento de la pila origen\n"
                	     << "seleccionada es mayor que elemento de la pila destino seleccionada." << endl;
                else
                	cout << "La jugada no se ha podido realizar porque has seleccionado alguna pila\n "
                	     << "que se sale del rango. Selecciona una pila entre 1 y 3." << endl;

                cout << endl;
            }
        }
        
        //Si salimos del while es porque el juego ha acabado. Preguntamos por una nueva partida
        cout << endl;
		cout << "***********************************************************************" << endl;
		cout << "*************************** !! ENHORABUENA !! *************************" << endl;
		cout << "********                Has completado la partida              ********" << endl;
		cout << endl;
		cout << endl;
		cout << "�Quieres empezar otra partida? [s/n]: ";
		cin >> comenzar;
    }
    
    
    //system("PAUSE");
    
    return 0;   
    
}
/************************************* Reglas ***************************************
*                                                                                   *
* Prototipo:                                                                        *
*     void Reglas ()                                                                *
*                                                                                   *
* Proposito:                                                                        *
*  Mostrar las reglas del juego Hanoi.                                              *
*                                                                                   *
* Paramatros:                                                                       *
*  Nombre        Tipo                E/S  Descripcion                               *
*  ------        ----------          ---  ------------                              *
*  No tiene parametros de entrada                                                   *
*                                                                                   *
*  Valor devuelto:                                                                  *
*  Ninguno                                                                          *
************************************************************************************/
void Reglas ()
{
    //Reglas del juego.
    cout << "Recuerda que las reglas del juego son:" << endl;
    cout << endl;
    cout << "\tS�lo se puede mover una carta en cada jugada, desde un mazo origen "<< endl;
    cout << " a un mazo destino." << endl;
    cout << endl;
    cout << "\tLa carta a mover debe ser la cima de un mazo, y al moverla se debe "<< endl;
    cout << " depositar sobre la cima de otra mazo." << endl;
    cout << endl;    
    cout << "\tLa jugada s�lo ser� v�lida si el numero de la carta a mover es inferior" << endl;
    cout << " al numero de la carta corresponde a la cima del mazo donde queremos dejarla." << endl;
    cout << endl;
}

/*********************************** Movimiento *************************************
*                                                                                   *
* Prototipo:                                                                        *
*     bool Movimiento(Hanoi &)                                                      *
*                                                                                   *
* Proposito:                                                                        *
*  Pide el movimiento que se quiere realizar y hace la llamada al metodo            *
*  movimiento de la clase hanoi.                                                    *
*                                                                                   *
* Paramatros:                                                                       *
*  Nombre        Tipo                E/S  Descripcion                               *
*  ------        ----------          ---  ------------                              *
*  hanoi         Hanoi               E/S   Objeto de la clase hanoi.                *
*                                                                                   *
*  Valor devuelto:                                                                  *
*        bool hecho                                                                 *
************************************************************************************/
bool Movimiento(Hanoi &hanoi, int &num_error)
{
    int aux1, aux2, origen, destino;
    bool hecho = false;
    
    //Pedimos el mazo origen y destino.
    cout << "Dime el mazo origen [1-3]: ";
    cin >> aux1;
    cout << "Dime el mazo destino [1-3]: ";
    cin >> aux2;
    
    //Comprobamos que los valores introducidos est�n dentro de los valores de 1 a 3

    if(aux1 > 0 && aux2 > 0 && aux1 < 4 && aux2 < 4)
    {
        //Restamos 1 al valor introducido para asignarlo a los indices de los mazos.
        origen = aux1 - 1;
        destino = aux2 - 1;
        //Comprobamos el movimiento y lo realizamos si es correcto
        if(hanoi.MoverCarta(origen, destino, num_error))
            hecho = true;
    }
    else
    	//Si las pilas seleccionadas no estan entre 1 y 3. Asignamos a este error el num 2.
    	num_error = 2;
    return hecho;
}
    
