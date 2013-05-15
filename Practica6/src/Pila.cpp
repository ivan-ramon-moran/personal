#include "Pila.h"


/************************************** Pila ****************************************
*                                                                                   *
* Prototipo:                                                                        *
*     Pila::Pila()                                                                  *
*                                                                                   *
* Proposito:                                                                        *
*  Constructor de la clase Pila que inicia la cima en -1.                           *
*                                                                                   *
* Paramatros:                                                                       *
*  Nombre        Tipo                E/S  Descripcion                               *
*  ------        ----------          ---  ------------                              *
*  No tiene parametros de entrada                                                   *
*                                                                                   *
*  Valor devuelto:                                                                  *
*  Ninguno                                                                          *
************************************************************************************/
Pila::Pila()
{
    //Asignamos a cima el valor de -1.
    cima = -1;
}

/************************************** Apilar **************************************
*                                                                                   *
* Prototipo:                                                                        *
*     bool Pila::Apilar(int x)                                                      *
*                                                                                   *
* Proposito:                                                                        *
*  Comprueba que la pila no está llena y si está vacía apila un elemento.           *
*                                                                                   *
* Paramatros:                                                                       *
*  Nombre        Tipo                E/S  Descripcion                               *
*  ------        ----------          ---  ------------                              *
*  x             int                  E   Elemento que queremos apilar.             *
*                                                                                   *
*  Valor devuelto:                                                                  *
*  bool ok                                                                          *
************************************************************************************/
bool Pila::Apilar(int x)
{
     //inicializamos el boleano a false.
     bool ok = false;
     
     //Comprobamos que la pila no estï¿½ llena
     if (cima != MAX - 1)
     {
         //Incrementamos cima en 1 posicion.
         cima++;
         //Asignamos a la posición de cima el valor x.
         vector[cima] = x;
         //Cambiamos el boleano.
         ok = true;
     }
     return ok;
}

/*********************************** Desapilar **************************************
*                                                                                   *
* Prototipo:                                                                        *
*     bool Pila::Desapilar()                                                        *
*                                                                                   *
* Proposito:                                                                        *
*  Comprueba que la pila no está vacía y si tiene al menos un elemento lo desapila. *
*                                                                                   *
* Paramatros:                                                                       *
*  Nombre        Tipo                E/S  Descripcion                               *
*  ------        ----------          ---  ------------                              *
*  No tiene parametros de entrada                                                   *
*                                                                                   *
*  Valor devuelto:                                                                  *
*  bool ok                                                                          *
************************************************************************************/
bool Pila::Desapilar()
{
     //Inicializamos el boleano a false.
     bool ok = false;
     
     //Comprobamos que la pila no está vacía.
     if (cima != -1)
     {
         //Decrementamos cima 1 posición.
         cima--;
         //Cambiamos el boleano a true.
         ok = true;
     }
     
     return ok;
}

/************************************* CimaPila *************************************
*                                                                                   *
* Prototipo:                                                                        *
*     bool Pila::CimaPila(int &x)                                                   *
*                                                                                   *
* Proposito:                                                                        *
*  Comprueba que la pila no está vacía y le asigna a x el valor de la cima.         *
*                                                                                   *
* Paramatros:                                                                       *
*  Nombre        Tipo                E/S  Descripcion                               *
*  ------        ----------          ---  ------------                              *
*  x             int                 E/S  Elemento en el que guardamos la cima.     *
*                                                                                   *
*  Valor devuelto:                                                                  *
*  bool ok                                                                          *
************************************************************************************/
bool Pila::CimaPila(int &x)
{
     //Incicializamos el boleano a false.
     bool ok = false;
     
     //Comprobamos que la pila no está vacía
     if (cima != -1)
     {
         //Asignamos a x el valor de la posición de cima.
         x = vector[cima];
         //Cambiamos el boleano.
         ok = true;
     }
     return ok;
}

/************************************ PilaVacia *************************************
*                                                                                   *
* Prototipo:                                                                        *
*     bool Pila::PilaVacia()                                                        *
*                                                                                   *
* Proposito:                                                                        *
*    Comprueba si la pila está vacía comparando cima con -1.                        *
*                                                                                   *
* Paramatros:                                                                       *
*  Nombre        Tipo                E/S  Descripcion                               *
*  ------        ----------          ---  ------------                              *
*  No tiene parametros de entrada                                                   *
*                                                                                   *
*  Valor devuelto:                                                                  *
*    bool                                                                           *
************************************************************************************/
bool Pila::PilaVacia()
{
    //Comparamos el valor de cima con -1 y devolvemos la respuesta.
    return (cima == -1);  
}

/********************************* ostream& operator<< *********************************
*                                                                                      *
* Prototipo:                                                                           *
*     ostream& operator<< (ostream& out, const Pila &pila)                             *
*                                                                                      *
* Proposito:                                                                           *
*  Sobrecargamos el operador << para poder mostrar la pila por pantalla.               *
*                                                                                      *
* Paramatros:                                                                          *
*  Nombre        Tipo                E/S  Descripcion                                  *
*  ------        ----------          ---  ------------                                 *
*  out           ostream             E/S  Salida de datos.                             *
*  pila          Pila                E/S  Objeto de la clase.                          *
*                                                                                      *
*  Valor devuelto:                                                                     *
*  ostream out                                                                         *
***************************************************************************************/
ostream& operator << (ostream& out, const Pila &pila)
{
    int i;
    
    //recorremos el resto del vector mostrando cada elemento separa por "  ".
    for (i = 0; i <= pila.cima; i++)
    {
        out << "  " << pila.vector[i];
    }
    
    return out;
}
