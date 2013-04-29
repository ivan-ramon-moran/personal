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

int GetNumCaracteres(char *cadenaPtr);

int main()
{
	char *palabra = "pene";
	char *buffer = "Hola, amigo";

	/*Es lo mismo que cout << buffer con la diferencia de que hay que especificar el numero
	de caracteres a mostrar*/
	cout.write(buffer, GetNumCaracteres(buffer));


	return 0;
}

//Redefinicion del metodo strlen

int GetNumCaracteres (char * cadenaPtr)
{
	//Num de caracteres vamos a ir incrementando
	int num_caracteres = 0;

	//Recorremos el puntero con aritmetica de punteros hasta que encontremos terminacion de cadena.
	while (*(cadenaPtr + num_caracteres) != '\0')
	{
		//Incrementamos el numero de caracteres en 1
		num_caracteres++;
	}

	return num_caracteres;
}


