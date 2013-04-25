#include "Fundacion.h"

//Constructores
//Contructor por defecto
/********************************** Fundacion********************************************
 *                                                                                      *
 *  Descripcion:  Constructor por defecto de la clase Fundacion   						*
 *                                                                                      *
 *  Parametros:  No tiene parametro de entrada                                          *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *                                                                                      *
 *  Valor devuelto: No devuelve nada (Constructor)                                      *
 ***************************************************************************************/

Fundacion::Fundacion(){}

//Contructor explicito
/********************************** Fundacion********************************************
 *                                                                                      *
 *  Descripcion:  Contructor explicito de la clase Fundacio, permite asignar los        *
 *                atributos al crear el objeto.                                         *
 *                                                                                      *
 *  Parametros:                                                                         *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *  nombre          string       E   Nombre de la fundacion que vamos a crear.          *
 *  saldo           float        E   saldo inicial de la fundacion                      *
 *                                                                                      *
 *  Valor devuelto: No devuelve nada (Contructor)                                       *
 ***************************************************************************************/

Fundacion::Fundacion(string nombre, float saldo)
{
	//Asignamos el nombre de la fundacion y el saldo.
	SetNombreFundacion(nombre);
	SetSaldo(saldo);

	//Asignamos tambien al campo presidente una cadena por defecto que indique que no hay presidente.
	presidente = "Sin presidente...";
}

//getters y setters

/********************************** GetNombreFundacon************************************
 *                                                                                      *
 *  Descripcion:  Permite obtener el nombre del objeto(Fundacion) que lo invoca       	*
 *                                                                                      *
 *  Parametros:  No tiene parametro de entrada                                          *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *                                                                                      *
 *  Valor devuelto: string, devuelve el nombre de la fundacion que invoque el metodo.   *
 ***************************************************************************************/

string Fundacion::GetNombreFundacion() const
{
	return this->nombre;
}

/********************************** SetNombreFundacion***********************************
 *                                                                                      *
 *  Descripcion:  Permite establecer el nombre del objeto(Fundacion) que lo invoca 	    *
 *                                                                                      *
 *  Parametros:                                                                         *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *  nombre          string      E    nombre de la fundacion                             *
 *                                                                                      *
 *  Valor devuelto: No devuelve nada                                                    *
 ***************************************************************************************/

void Fundacion::SetNombreFundacion(string nombre)
{
	this->nombre = nombre;
}

/********************************** GetSaldo*********************************************
 *                                                                                      *
 *  Descripcion:  Permite obtener el saldo del objeto(Fundacion) que lo invoca       	*
 *                                                                                      *
 *  Parametros:  No tiene parametro de entrada                                          *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *                                                                                      *
 *  Valor devuelto: float, devuelve el saldo de la fundacion que invoque el metodo.     *
 ***************************************************************************************/

float Fundacion::GetSaldo() const
{
	return this->saldo;
}

/********************************** SetSaldo*********************************************
 *                                                                                      *
 *  Descripcion:  Permite establecer el saldo del objeto(Fundacion) que lo invoca 	    *
 *                                                                                      *
 *  Parametros:                                                                         *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *  saldo           float        E    saldo de la fundacion                             *
 *                                                                                      *
 *  Valor devuelto: No devuelve nada                                                    *
 ***************************************************************************************/

void Fundacion::SetSaldo(float saldo)
{
	this->saldo = saldo;
}

/********************************** GetNombrePresidente**********************************
 *                                                                                      *
 *  Descripcion:  Permite obtener el presidente del objeto(Fundacion) que lo invoca       	*
 *                                                                                      *
 *  Parametros:  No tiene parametro de entrada                                          *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *                                                                                      *
 *  Valor devuelto: float, devuelve el saldo de la fundacion que invoque el metodo.     *
 ***************************************************************************************/

string Fundacion::GetDNIPresidente() const
{
	return this->presidente;
}

/********************************** SetNombrePresidente**********************************
 *                                                                                      *
 *  Descripcion:  Permite establecer el presidente objeto(Fundacion) que lo invoca 	    *
 *                                                                                      *
 *  Parametros:                                                                         *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *  dni             string       E    dni del presidente                                *
 *                                                                                      *
 *  Valor devuelto: No devuelve nada                                                    *
 ***************************************************************************************/

bool Fundacion::SetDNIPresidente(string dni)
{
	bool es_miembro = false;
	int posicion;

	//Miramos si existe el miembro en la lista de mimbros
	posicion = BuscarMiembro(dni);

	if (posicion != -1)
	{
		//Si existe, añadimos el presidente
		this->presidente = dni;
		es_miembro = true;
	}

	//Si no existe no hacemos nada
	return es_miembro;
}

/********************************** IngresarDinero***************************************
 *                                                                                      *
 *  Descripcion:  Permite ingresar dinero en el objeto(Fundacion) que lo invoca 	    *
 *                                                                                      *
 *  Parametros:                                                                         *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *  cantidad        float       E    cantidad de dinero a ingresar                      *
 *                                                                                      *
 *  Valor devuelto: bool, devuelve el resultado de la operacion                         *
 ***************************************************************************************/

bool Fundacion::IngresarDinero(float cantidad)
{
	bool ok = false;

	//Si la cantidad es positiva la ingresamos, si es negativa no hacemos nada.
	if (cantidad > 0)
	{
		this->saldo += cantidad;
		ok = true;
	}

	return ok;
}

/********************************** RetirarDinero***************************************
 *                                                                                      *
 *  Descripcion:  Permite retirar dinero del objeto(Fundacion) que lo invoca 	        *
 *                                                                                      *
 *  Parametros:                                                                         *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *  cantidad        float       E    cantidad de dinero a retirar                       *
 *                                                                                      *
 *  Valor devuelto: bool, devuelve el resultado de la operacion                         *
 ***************************************************************************************/

bool Fundacion::RetirarDinero(float cantidad)
{
	bool ok = false;

	//Si tenemos más saldo del que queremos retirar, permitimos la operacion, si no no hacemos nada.
	if (this->saldo >= cantidad && cantidad > 0)
	{
		this->saldo -= cantidad;
		ok = true;
	}

	return ok;
}

/********************************** AgregarMiembro***************************************
 *                                                                                      *
 *  Descripcion:  Permite agregar un nuevo miembro en el objeto(Fundacion) que lo invoca*
 *                                                                                      *
 *  Parametros:                                                                         *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *  Persona         Persona     E/S  objeto persona a añadir                            *
 *                                                                                      *
 *  Valor devuelto: bool, devuelve el resultado de la operacion                         *
 ***************************************************************************************/

bool Fundacion::AgregarMiembro(const Persona &p)
{
	bool ok = false;
	int posicion;

	//Siempre y cuando el miembro no esta ya en la lista, permitimos la operacion.
	posicion = BuscarMiembro(p.GetDNI());

	if (posicion == -1)
	{
		miembros.push_back(p);
		ok = true;
	}

	return ok;
}

/********************************** BuscarMiembro****************************************
 *                                                                                      *
 *  Descripcion:  Permite buscar un miembro en el objeto(Fundacion) que lo invoca       *
 *                                                                                      *
 *  Parametros:                                                                         *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *  dni             string      E    dni de la persona que estamos buscando.            *
 *                                                                                      *
 *  Valor devuelto: int, devuelve la posicion de la persona si la encuentra o -1        *
 *  				en caso contrario.                                                  *
 ***************************************************************************************/

int Fundacion::BuscarMiembro(string dni)
{
	int posicion = -1;

	//Busacamos si existe un miembro con el mismo dni que le pasamos a la funcion como parametro.
	for (unsigned int i = 0; i < miembros.size(); i++)
		if (miembros[i].GetDNI() == dni)
			posicion = i;

	//devolvemos -1 si no existe ningun miembro con el dni buscado, o el indice si si que existe.

	return posicion;
}

/********************************** DesligarMiembro**************************************
 *                                                                                      *
 *  Descripcion:  Permite eliminar un miembro en el objeto(Fundacion) que lo invoca     *
 *                                                                                      *
 *  Parametros:                                                                         *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *  dni             string      E    dni de la persona que vamos a eliminar             *
 *                                                                                      *
 *  Valor devuelto: bool, el resultado de la operacion.                                 *
 ***************************************************************************************/

bool Fundacion::DesligarMiembro(string dni)
{
	bool ok = false;
	int posicion;

	//Buscamos el miembro, ya que no tiene sentido desligar a un miebro que no exista en la lista.
	posicion = BuscarMiembro(dni);

	if (posicion != -1)
	{
		//En el caso de que exista el miembro en el vector
		//Comprobamos si es el presidente, si lo es ponemos a la fundacion que no tiene presidente.
		if (miembros[posicion].GetDNI() == GetDNIPresidente())
			SetDNIPresidente("La fundacion no tiene presidente");

		//Eliminamos la persona del vector
		miembros[posicion] = miembros.back();
		miembros.pop_back();
		ok = true;
	}

	return ok;
}

//Sobrecargas de operadores

/********************************** operator+********************************************
 *                                                                                      *
 *  Descripcion:  Permite ingresar dinero en el objeto(Fundacion) que lo invoca mediante*
 *                el operador +.                                                                      *
 *  Parametros:                                                                         *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *  cantidad        float       E    cantidad de dinero a ingresar                      *
 *                                                                                      *
 *  Valor devuelto: bool, devuelve el resultado de la operacion                         *
 ***************************************************************************************/

bool Fundacion::operator+(int cantidad)
{
	//Sobrecarga del operador + que nos permite ingresar dinero de la forma f + 200;
	bool ok;

	ok = IngresarDinero(cantidad);

	return ok;
}

/********************************** operator-********************************************
 *                                                                                      *
 *  Descripcion:  Permite retirar dinero en el objeto(Fundacion) que lo invoca mediante *
 *                el operador -.                                                                      *
 *  Parametros:                                                                         *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *  cantidad        float       E    cantidad de dinero a retirar                       *
 *                                                                                      *
 *  Valor devuelto: bool, devuelve el resultado de la operacion                         *
 ***************************************************************************************/

bool Fundacion::operator-(int cantidad)
{
	//Sobrecarga del operador - que nos permite retirar dinero de la forma f - 200;
	bool ok;

	ok = RetirarDinero(cantidad);

	return ok;
}

/********************************** operator+********************************************
 *                                                                                      *
 *  Descripcion:  Permite ingresar un nuevo miembro en el objeto(Fundacion)             *
 *  que lo invoca mediante el operador +.                                               *
 *  Parametros:                                                                         *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *  p               Persona     E/S  miembro a ingresar                                 *
 *                                                                                      *
 *  Valor devuelto: bool, devuelve el resultado de la operacion                         *
 ***************************************************************************************/

bool Fundacion::operator+(Persona &p)
{
	//Sobrecarga del operador + que nos permite añadir un miebro de la forma f + persona;
	bool ok;

	ok = AgregarMiembro(p);

	return ok;
}

/********************************** operator-********************************************
 *                                                                                      *
 *  Descripcion:  Permite eliminar un nuevo miembro en el objeto(Fundacion)             *
 *  que lo invoca mediante el operador -.                                               *
 *  Parametros:                                                                         *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *  dni             string      E/S  DNI de la persona a eliminar                       *
 *                                                                                      *
 *  Valor devuelto: bool, devuelve el resultado de la operacion                         *
 ***************************************************************************************/

bool Fundacion::operator-(string dni)
{
	//Sobrecarga del operador - que nos permite quitar un miebro de la forma f - persona;
	bool ok;

	ok = DesligarMiembro(dni);

	return ok;
}

/********************************** operator<<*******************************************
 *                                                                                      *
 *  Descripcion:  Permite imprimir los datos de la fundacion                            *
 *                                                                                      *
 *  Parametros:  No tiene parametro de entrada                                          *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *
 *  out             ostream     E/S  objeto ostream hacia donde dirigiremos la salida.  *
 *  f               Fundacion   E/S  objeto fundacion del que vamos a imprimir los      *
 *  								 atributos.	                                        *
 *                                                                                      *
 *  Valor devuelto: devuelve los 2 parametros de entrada por referencia.                *
 ***************************************************************************************/

ostream& operator<< (ostream &out, Fundacion &f)
{
	/*Sobrecarga del operador de flujo de salida que nos permite imprimir los datos de una fundacion
	de la forma cout << fundacion;*/
	string nombre_presidente = "Sin presidente...";

	//Buscamos el presidente para obtener su nombre.
	int indice = f.BuscarMiembro(f.presidente);

	out << "----------------------------------------------" << endl;
	out << "            DATOS DE LA FUNDACION             " << endl;
	out << "----------------------------------------------" << endl;


	if (indice != -1)
	{
		//Obtenemos la persona que representa al presidente
		Persona p = f.miembros[indice];
		//Asignamos su nombre a nombre_presidente para poder mostrarlo.
		nombre_presidente = p.GetNombre() + " " + p.GetApellido1() + " " + p.GetApellido2();
	}

	out << endl << "Nombre: " << f.nombre << endl;
	out << "Presidente: " << nombre_presidente << endl;
	out << "saldo: " << f.saldo << " €" << endl;

	return out;
}

/********************************** ImprimirLista****************************************
 *                                                                                      *
 *  Descripcion:  Permite imprimir la lista de miembros que hay en el objeto(Fundacion) *
 *  que lo invoca mediante el operador -.                                               *
 *  Parametros: No tiene parametros de entrada                                          *
 *  Nombre          Tipo        E/S  Descripcion                                        *
 *  ------          ----------  ---  ------------                                       *                     *
 *                                                                                      *
 *  Valor devuelto: No devuelve nada                                                    *
 ***************************************************************************************/

void Fundacion::ImprimirLista()
{
	/*Funcion que nos permite imprimir una lista de miembros mediante la sobrecaga definida en la
	clase Persona.cpp de la forma cout << persona;*/
	cout << "--------------------------------------------" << endl;
	cout << "              LISTA MIEMBROS                " << endl;
	cout << "--------------------------------------------" << endl;

	//Recorremos con un for la lista de miembros y imprimimos sus datos.
	for (unsigned int i = 0; i < miembros.size(); i++)
	{
		cout << endl << "Miembro: " << i << endl;
		cout << miembros[i] << endl;
	}

	if (miembros.size() == 0)
	{
		cout << endl << "La fundacion no tiene miembros" << endl;
	}
}
