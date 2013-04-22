// Fig. 13.2: EmpleadoPorComision.cpp
// Definiciones de las funciones miembro de EmpleadoPorComision.
#include <iostream>

using namespace std;

#include "EmpleadoPorComision.h" // definición de la clase EmpleadoPorComision

// constructor
EmpleadoPorComision::EmpleadoPorComision(const string &nombre, const string &apellido, const string &nss, double ventas, double tarifa )
:apellidoPaterno( apellido ), numeroSeguroSocial( nss )
{
	setVentasBrutas( ventas ); // valida y almacena las ventas brutas
	setPrimerNombre(nombre); 
	
	cout << "La direccion de memoria de la variable nombre en el main es: " << &nombre << endl; 
	cout << "La direccion de memoria del atributo nombre del objeto es : " << &nombre << endl; 
	//setTarifaComision( tarifa ); // valida y almacena la tarifa de comisión
} // fin del constructor de EmpleadoPorComision

// establece el primer nombre
void EmpleadoPorComision::setPrimerNombre( const string &nombre )
{
	primerNombre = nombre; // debe validar
} // fin de la función setPrimerNombre

// devuelve el primer nombre
string EmpleadoPorComision::getPrimerNombre() const
{
	return primerNombre;
} // fin de la función getPrimerNombre

// establece el apellido paterno
void EmpleadoPorComision::setApellidoPaterno( const string &apellido )
{
	apellidoPaterno = apellido; // debe validar
} // fin de la función setApellidoPaterno

// devuelve el apellido paterno
string EmpleadoPorComision::getApellidoPaterno() const
{
	return apellidoPaterno;
} // fin de la función getApellidoPaterno
// establece el número de seguro social
void EmpleadoPorComision::setNumeroSeguroSocial( const string &nss )
{
	numeroSeguroSocial = nss; // debe validar
} // fin de la función setNumeroSeguroSocial

// devuelve el número de seguro social
string EmpleadoPorComision::getNumeroSeguroSocial() const
{
	return numeroSeguroSocial;
} // fin de la función getNumeroSeguroSocial

// establece el monto de ventas brutas
void EmpleadoPorComision::setVentasBrutas( double ventas )
{
	ventasBrutas = ( ventas < 0.0 ) ? 0.0 : ventas;
} // fin de la función setVentasBrutas

// devuelve el monto de ventas brutas
double EmpleadoPorComision::getVentasBrutas() const
{
	return ventasBrutas;
} // fin de la función getVentasBrutas

// establece la tarifa de comisión
void EmpleadoPorComision::setTarifaComision( double tarifa )
{
	tarifaComision = ( tarifa > 0.0 && tarifa < 1.0 ) ? tarifa : 0.0;
} // fin de la función setTarifaComision

// devuelve la tarifa de comisión
double EmpleadoPorComision::getTarifaComision() const
{
	return tarifaComision;
} // fin de la función getTarifaComision

// calcula los ingresos
double EmpleadoPorComision::ingresos() const
{
	return getTarifaComision() * getVentasBrutas();
} // fin de la función ingresos

// imprime el objeto EmpleadoPorComision
void EmpleadoPorComision::imprimir() const
{
	cout << "empleado por comision: " << getPrimerNombre() << ' ' << getApellidoPaterno()
		 << "\nnumero de seguro social: " << getNumeroSeguroSocial()
		 << "\nventas brutas: " << getVentasBrutas()
	     << "\ntarifa de comision: " << getTarifaComision();
} // fin de la función imprimir

