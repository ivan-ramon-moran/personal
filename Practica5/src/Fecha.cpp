
/************************** Fecha.cpp ****************************************
 *
 *  Proposito: Implementacion de los metodos propios de la clase Fecha
 *             asi como las funciones 'friend'
 *
 *  Historial del Desarrollo:
 *  Fecha       Autor              Id Cambio  Version  Descripcion del cambio
 *  ----------  ------------------ ---------  -------  ----------------------
 *  16-04-2013  Ricardo Ferris          0      0.9
 *****************************************************************************/

#include "Fecha.h"

/*************** Fecha::Fecha (void) *****************************************
 *
 *  Descripcion:  Constructor por defecto de la clase.
 *                Inicia el objeto a una fecha correcta
 *
 *  Parametros:
 *  Nombre          Tipo        E/S  Descripcion
 *  ------          ----------  ---  ------------
 *  ninguno
 *
 *  Valor devuelto:
 *  Ninguno
 ****************************************************************************/
Fecha::Fecha (void)
{
    dia = 1;
    mes = 1;
    anyo = 2010;
}

/*************** Fecha Fecha::IniciarFecha (int d, int m, int a )*************
 *
 *  Descripcion:  Inicia el objeto con la fecha (dia, mes y anyo pasados
 *                como parametro. NO se hace ningun tipo de comprobacion
 *                sobre si los valores pasados son o no correctos
 *
 *  Parametros:
 *  Nombre          Tipo        E/S  Descripcion
 *  ------          ----------  ---  ------------
 *  d               int         E    dia de la fecha
 *  m               int         E    mes de la fecha
 *  a               int         E    anyo de la fecha
 *
 *  Valor devuelto:
 *  Fecha   devuelve el propio objeto
 *****************************************************************************/
Fecha Fecha::IniciarFecha (int d, int m, int a)
{
    dia = d;
    mes = m;
    anyo = a;
    
    return *this;
}

/*************** ostream& operator<< (ostream& out, Fecha fec) ***************
 *
 *  Descripcion:  Sobrecarga del operador <<
 *                Funcion 'friend' de la clase
 *
 *  Parametros:
 *  Nombre          Tipo        E/S  Descripcion
 *  ------          ----------  ---  ------------
 *  out             ostream     E S  Flujo de salida donde se escribira la 
 *                                   informacion
 *  fec             Fecha       E    Fecha a mostrar en el flujo de salida
 *
 *  Valor devuelto:
 *  ostream&   devuelve una referencia al propio flujo de salida
 *****************************************************************************/
ostream& operator<< (ostream& out, const Fecha &fec)
{
    out << fec.dia << "/" << fec.mes << "/" << fec.anyo;

    return out;
}

/*************** istream& operator>> (istream& in, Fecha & fec) **************
 *
 *  Descripcion:  Sobrecarga del operador >>
 *                Funcion 'friend' de la clase
 *
 *  Parametros:
 *  Nombre          Tipo        E/S  Descripcion
 *  ------          ----------  ---  ------------
 *  in              istream     E S  Flujo de entrada del que leeremos la 
 *                                   informacion
 *  fec             Fecha         S  Variable en la que pondremos la informacion
 *                                   leida del flujo de entrada
 *
 *  Valor devuelto:
 *  istream&   devuelve una referencia al propio flujo de entrada
 *****************************************************************************/
istream& operator>> (istream& in, Fecha & fecha)
{
	char c_aux;
	
    in >> fecha.dia >> c_aux >> fecha.mes >> c_aux >> fecha.anyo;
    
    return in;
}

/*************** bool operator< (Fecha & fec1, Fecha & fec2) *****************
 *
 *  Descripcion:  Sobrecarga del operador < (comparaci�n de fechas)
 *                Funcion 'friend' de la clase
 *
 *  Parametros:
 *  Nombre          Tipo        E/S  Descripcion
 *  ------          ----------  ---  ------------
 *  fec1            Fecha       E    Primera fecha a comparar
 *  fec2            Fecha       E    Segunda fecha a comparar
 *
 *  Valor devuelto:
 *  bool   true si la primera fecha es anterior a la segunda
 *         false en caso contrario (igual o posterior)
 *****************************************************************************/
bool Fecha::operator< (Fecha &fecha2)
{
	int i_fec1, i_fec2;
	
    i_fec1 = Fecha2Int ();
    i_fec2 = fecha2.Fecha2Int ();
    
    return i_fec1 < i_fec2;
}

/*************** int Fecha::Fecha2Int () *************************************
 *
 *  Descripcion:  Convierte la fecha que hace la llamada al metodo en un
 *                entero unico y facil de comparar
 *
 *  Parametros:
 *  Nombre          Tipo        E/S  Descripcion
 *  ------          ----------  ---  ------------
 *
 *  Valor devuelto:
 *  int    Entero equivalente a la fecha
 *****************************************************************************/
int Fecha::Fecha2Int ()
{
    return anyo * 10000 + mes * 100 + dia;
}

bool Fecha::operator>(Fecha &fecha2)
{
	int i_fec1, i_fec2;

	i_fec1 = Fecha2Int();
	i_fec2 = fecha2.Fecha2Int();

	return i_fec1 > i_fec2;
}

void Fecha::ImprimirFecha()
{
	cout << dia << "/" << mes << "/" << anyo << endl;
}
