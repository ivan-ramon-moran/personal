// Fig. 13.5: fig13_05.cpp
// Cómo orientar los apuntadores de la clase base y la clase derivada a los
// objetos de la clase base y la clase derivada, respectivamente.
#include <iostream>
#include <iomanip>
#include "EmpleadoPorComision.h"
#include "EmpleadoBaseMasComision.h"

using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;


int main()
{
	EmpleadoPorComision *emBasePtr;
	EmpleadoBaseMasComision emDerivado("Pedro", "J.Santos","1111",10000, 0.06,300);
	
	emBasePtr = &emDerivado;
	emBasePtr->imprimir();
}
