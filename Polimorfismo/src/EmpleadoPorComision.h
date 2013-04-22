// Fig. 13.1: EmpleadoPorComision.h
// Definición de la clase EmpleadoPorComision que representa a un empleado por comisión.

#ifndef COMISION_H
#define COMISION_H
#include <string> // clase string estándar de C++

#include <iostream>

using namespace std;

class EmpleadoPorComision
{
public:
	EmpleadoPorComision( const string &, const string &, const string &, double = 0.0, double = 0.0 );

	void setPrimerNombre( const string & ); // establece el primer nombre
	string getPrimerNombre() const; // devuelve el primer nombre

	void setApellidoPaterno( const string & ); // establece el apellido paterno
	string getApellidoPaterno() const; // devuelve el apellido paterno

	void setNumeroSeguroSocial( const string & ); // establece el NSS
	string getNumeroSeguroSocial() const; // devuelve el NSS

	void setVentasBrutas( double ); // establece el monto de ventas brutas
	double getVentasBrutas() const; // devuelve el monto de ventas brutas

	void setTarifaComision( double ); // establece la tarifa de comisión
	double getTarifaComision() const; // devuelve la tarifa de comisión

	double ingresos() const; // calcula los ingresos
	virtual void imprimir() const; // imprime el objeto EmpleadoPorComision
	virtual void virtualPura() = 0;
private:
	string primerNombre;
	string apellidoPaterno;
	string numeroSeguroSocial;
	double ventasBrutas; // ventas brutas por semana
	double tarifaComision; // porcentaje de comisión
}; // fin de la clase EmpleadoPorComision
#endif


