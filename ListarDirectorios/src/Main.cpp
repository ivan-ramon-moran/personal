//============================================================================
// Name        : ListarDirectorios.cpp
// Author      : K 3 r N e L
// Version     :
// Copyright   : Free Software for free World!!!
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <dirent.h> // Para listar directorios
#include <sys/stat.h>	//Para crear directorio
#include <errno.h> //Para errno
#include <stdio.h> //Para el remove
#include "Directorio.h"

using namespace std;

int main()
{

	//ListarDirectorio("/home/k3rnel/Escritorio");
	cout << Directorio::BorrarFileDir("/home/k3rnel/Escritorio/gay");

	return 0;
}



