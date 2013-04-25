#include <stdexcept>
#include <iostream>

using namespace std;

class Excepcion:public runtime_error
{
public:
	Excepcion()
		:runtime_error("No se puede dividir entre 0"){}
};
