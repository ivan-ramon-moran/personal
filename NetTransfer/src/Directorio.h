#include <iostream>
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <vector>
#include <exception>
#include <fstream>

#ifndef DIRECTORIO_H_
#define DIRECTORIO_H_

using namespace std;

class Directorio
{
public:
	Directorio();

	static int BorrarFileDir(string path);
	static int CrearDirectorio(string path);
	static int RenombrarFileDir(string path_origen, string path_destino);
	static void ListarDirectorio(string &path, vector<string> &vector);
	static  bool GetFileSize(string path, unsigned long long &file_size);
};

#endif /* DIRECTORIO_H_ */
