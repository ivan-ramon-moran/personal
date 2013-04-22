// Fig. 13.4: EmpleadoBaseMasComision.cpp
// Definiciones de las funciones miembro de la clase EmpleadoBaseMasComisi#include <iostream>

// definición de la clase EmpleadoBaseMasComision
#include "EmpleadoBaseMasComision.h"

// constructor
EmpleadoBaseMasComision::EmpleadoBaseMasComision(const string &nombre, const string &apellido, const string &nss, double ventas, double tarifa, double salario )
// llama en forma explícita al constructor de la clase base
: EmpleadoPorComision( nombre, apellido, nss, ventas, tarifa )
{
	setSalarioBase( salario ); // valida y almacena el salario base
} // fin del constructor de EmpleadoBaseMasComision

// establece el salario base
void EmpleadoBaseMasComision::setSalarioBase( double salario )
{
	salarioBase = ( salario < 0.0 ) ? 0.0 : salario;
} // fin de la función setSalarioBase

// devuelve el salario base
double EmpleadoBaseMasComision::getSalarioBase() const
{
	return salarioBase;
} // fin de la función getSalarioBase

// calcula los ingresos
double EmpleadoBaseMasComision::ingresos() const
{
	return getSalarioBase() + EmpleadoPorComision::ingresos();
} // fin de la función ingresos

// imprime el objeto EmpleadoBaseMasComision
void EmpleadoBaseMasComision::imprimir() const
{
	cout << "con salario base ";
	// invoca a la función imprimir de EmpleadoPorComision
	EmpleadoPorComision::imprimir();
	cout << "\nsalario base: " << getSalarioBase();
} // fin de la función imprimir

void EmpleadoBaseMasComision::virtualPura()
{
	cout << "Implemento el metodo virtual puro heredado" << endl;
}
