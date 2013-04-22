// Fig. 13.3: EmpleadoBaseMasComision.h
// Clase EmpleadoBaseMasComision derivada de la clase
// EmpleadoPorComision.
#ifndef BASEMAS_H
#define BASEMAS_H
#include <string> // clase string estándar de C++

using std::string;

#include "EmpleadoPorComision.h" // declaración de la clase EmpleadoPorComision

class EmpleadoBaseMasComision : public EmpleadoPorComision
{
public:
	EmpleadoBaseMasComision( const string &, const string &,
	const string &, double = 0.0, double = 0.0, double = 0.0 );
	
	void setSalarioBase( double ); // establece el salario base
	double getSalarioBase() const; // devuelve el salario base
	
	double ingresos() const; // calcula los ingresos
	virtual void imprimir() const; // imprime el objeto EmpleadoBaseMasComision
	void virtualPura(); //Funcion virtual pura!!!
private:
	double salarioBase; // salario base
}; // fin de la clase EmpleadoBaseMasComision
#endif

