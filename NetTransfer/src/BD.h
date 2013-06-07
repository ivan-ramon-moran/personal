#include <iostream>
#include <sqlite3.h>

using namespace std;

#ifndef BD_H_
#define BD_H_

class BD {
public:
	BD();
	virtual ~BD();

	static bool ComprobarConsulta(string nombre_bd, string sentencia);
	static bool EjecutarOperacion(string nombre_bd, string sentencia);

};

#endif /* BD_H_ */
