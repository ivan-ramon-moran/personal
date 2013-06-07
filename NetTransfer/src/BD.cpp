#include "BD.h"

BD::BD()
{

}

BD::~BD() {
	// TODO Auto-generated destructor stub
}

bool BD::ComprobarConsulta(string nombre_bd, string sentencia)
{
	bool existe = false;
	sqlite3 *db;
	sqlite3_stmt *resultado;
	const char* siguiente;      /* puntero a la siguiente sentencia */
	int res_ope;

	res_ope = sqlite3_open(nombre_bd.c_str(), &db);
	res_ope = sqlite3_prepare(db, sentencia.c_str(), sentencia.length(), &resultado, &siguiente);

	if (sqlite3_step(resultado) == SQLITE_ROW)
		existe = true;

	sqlite3_close(db);

	return existe;
}

bool BD::EjecutarOperacion(string nombre_bd, string sentencia)
{
	bool realizada = false;
	sqlite3 *db;
	int res_ope;
	char *error;

	res_ope = sqlite3_open(nombre_bd.c_str(), &db);
	res_ope = sqlite3_exec(db, sentencia.c_str(), NULL, NULL, &error);

	if (res_ope == SQLITE_OK)
		realizada = true;

	sqlite3_close(db);

	return realizada;
}
