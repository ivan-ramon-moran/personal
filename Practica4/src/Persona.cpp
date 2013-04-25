#include "Persona.h"

//Constructores

//Contructor por defecto
/********************************** Persona *********************************************
 *                                                                                      *
 *  Descripcion:  Constructor por defecto de la clase Persona     						*
 *                                                                                      *
 *  Parametros:  No tiene parametro de entrada                                          *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *                                                                                      *
 *  Valor devuelto: No devuelve valor (Constructor)                                     *
 ***************************************************************************************/
Persona::Persona(){}

//Contructor explicito
/********************************** Persona *********************************************
 *                                                                                      *
 *  Descripcion:  Contructor explicito de la clase Persona, permite asignar los         *
 *                atributos al crear el objeto.                                         *
 *                                                                                      *
 *  Prototipo: 	  Persona::Persona(string dni, string nombre, string apellido1,         *
 *  			  string apellido2)                                                     *
 *                                                                                      *
 *  Parametros:                                                                         *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *  dni             string       E   DNI de la persona que vamos a crear.               *
 *  nombre          string       E   Nombre de la persona que vamos a crear.            *
 *  apellido1       string       E   Primero apellido de la persona que vamos a crear   *
 *  apellido2       string       E   Segundo apellido de la persona que vamos a crear   *
 *                                                                                      *
 *  Valor devuelto: No devuelve nada (Contructor)                                                       *
 ***************************************************************************************/

Persona::Persona(string dni, string nombre, string apellido1, string apellido2)
{
	//Asignamos DNI, nombre y apellidos a la persona que estamos creando mediante setters.
	SetDNI(dni);
	SetNombre(nombre);
	SetApellido1(apellido1);
	SetApellido2(apellido2);
}

//Getters y setters

/********************************** GetDNI *********************************************
 *                                                                                      *
 *  Descripcion:  Permite obtener el dni del objeto(Persona) que lo invoca     			*
 *                                                                                      *
 *  Parametros:  No tiene parametro de entrada                                          *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *                                                                                      *
 *  Valor devuelto: string, devuelve el dni de la persona que invoque el metodo.        *
 ***************************************************************************************/

string Persona::GetDNI() const
{
	return this->dni;
}

/********************************** SetDNI **********************************************
 *                                                                                      *
 *  Descripcion:  Permite establecer el dni del objeto(Persona) que lo invoca     	    *
 *                                                                                      *
 *  Parametros:                                                                         *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *  dni             string      E    dni de la persona                                  *
 *                                                                                      *
 *  Valor devuelto: No devuelve nada                                                    *
 ***************************************************************************************/

void Persona::SetDNI(string dni)
{
	this->dni = dni;
}

/********************************** GetNombre *******************************************
 *                                                                                      *
 *  Descripcion:  Permite obtener el nombre del objeto(Persona) que lo invoca     	    *
 *                                                                                      *
 *  Parametros:  No tiene parametro de entrada                                          *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *                                                                                      *
 *  Valor devuelto: string, devuelve el nombre de la persona que invoque el metodo.        *
 ***************************************************************************************/

string Persona::GetNombre() const
{
	return this->nombre;
}

/********************************** SetNombre *******************************************
 *                                                                                      *
 *  Descripcion:  Permite establecer el nombre del objeto(Persona) que lo invoca        *
 *                                                                                      *
 *  Parametros:                                                                         *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *  nombre          string      E    nombre de la persona.                              *
 *                                                                                      *
 *  Valor devuelto: no devuelve nada.                                                   *
 ***************************************************************************************/

void Persona::SetNombre(string nombre)
{
	this->nombre = nombre;
}

/********************************** GetApellido1 ****************************************
 *                                                                                      *
 *  Descripcion:  Permite obtener el primer pellido del objeto(Persona) que lo invoca   *
 *                                                                                      *
 *  Parametros:  No tiene parametro de entrada                                          *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *                                                                                      *
 *  Valor devuelto: string, devuelve el p. apellido de la persona que invoque el metodo.*
 ***************************************************************************************/

string Persona::GetApellido1() const
{
	return this->apellido1;
}

/********************************** SetApellido1*****************************************
 *                                                                                      *
 *  Descripcion:  Permite establecer el p. apellido del objeto(Persona) que lo invoca   *
 *                                                                                      *
 *  Parametros:  No tiene parametro de entrada                                          *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *  apellido1       string      E    primer apellido de la persona.                     *
 *                                                                                      *
 *  Valor devuelto: no devuelve nada                                                    *
 ***************************************************************************************/

void Persona::SetApellido1(string apellido1)
{
	this->apellido1 = apellido1;
}

/********************************** GetApellido2 ****************************************
 *                                                                                      *
 *  Descripcion:  Permite obtener el segundo pellido del objeto(Persona) que lo invoca  *
 *                                                                                      *
 *  Parametros:  No tiene parametro de entrada                                          *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *                                                                                      *
 *  Valor devuelto: string, devuelve el s. apellido de la persona que invoque el metodo.*
 ***************************************************************************************/

string Persona::GetApellido2() const
{
	return this->apellido2;
}

/********************************** SetApellido2*****************************************
 *                                                                                      *
 *  Descripcion:  Permite establecer el s. apellido del objeto(Persona) que lo invoca   *
 *                                                                                      *
 *  Parametros:  No tiene parametro de entrada                                          *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *  apellido2       string      E    segundo apellido de la persona.                    *
 *                                                                                      *
 *  Valor devuelto: no devuelve nada                                                    *
 ***************************************************************************************/

void Persona::SetApellido2(string apellido2)
{
	this->apellido2 = apellido2;
}

/********************************** operator<<*******************************************
 *                                                                                      *
 *  Descripcion:  Permite imprimir los datos de la persona                              *
 *                                                                                      *
 *  Parametros:  No tiene parametro de entrada                                          *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *  out             ostream     E/S  objeto ostream hacia donde dirigiremos la salida.  *
 *  p               Persona     E/S  objeto persona del que vamos a imprimir los        *
 *  								 atributos.	                                        *
 *                                                                                      *
 *  Valor devuelto: devuelve los 2 parametros de entrada por referencia.                *
 ***************************************************************************************/

ostream& operator<<(ostream &out, const Persona &p)
{
	/*Sobrecarga del operador de flujo << que nos permite imprimir los datos de una persona de la
	forma cout << persona;*/
	out << "Nombre: " << p.nombre << endl;
	out << "Primer apellido: " << p.apellido1 << endl;
	out	<< "Segundo apellido: " << p.apellido2 << endl;
	out	<< "DNI: " << p.dni << endl;

	return out;
}
