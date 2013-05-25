//============================================================================
// Name        : SQLite.cpp
// Author      : K 3 r N e L
// Version     :
// Copyright   : Free Software for free World!!!
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sqlite3.h>

using namespace std;

int main()
{
	sqlite3 *data_base;
	sqlite3_stmt *resultado;
	char *error;
	string sentencia;
	int res_ope;

	res_ope = sqlite3_open("NetTransfer.db", &data_base);
	sentencia = "CREATE TABLE usuarios(id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, usuario TEXT NOT NULL, password TEXT_NOT_NULL)";
	res_ope = sqlite3_exec(data_base,sentencia.c_str(),NULL,NULL,&error);

	if (res_ope == SQLITE_OK)
		cout << "Operacion realizada!!!" << endl;

	sqlite3_close(data_base);

	cout << "NetTransfer" << endl; // prints NetTransfer
	return 0;
}
