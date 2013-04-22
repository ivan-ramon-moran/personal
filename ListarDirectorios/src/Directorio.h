#ifndef DIRECTORIO_H_
#define DIRECTORIO_H_

#include <iostream>
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

using namespace std;

class Directorio
{
public:
	Directorio();

	static int BorrarFileDir(string path);
	static int CrearDirectorio(string path);
	static int RenombrarFileDir(string path_origen, string path_destino);
	static void ListarDirectorio(string path);


};

#endif /* DIRECTORIO_H_ */
