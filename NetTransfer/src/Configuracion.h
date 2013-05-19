#ifndef CONF_H__
#define CONF_H__

#include <iostream>
#include "FileViewer.h"
#include "Cliente.h"
#include "Server.h"

using namespace std;

class Configuracion
{
public:
	Configuracion();

	//Metodo para devolver la instancia de la clase
	static Configuracion* get_instance();

	//Atributos
	FileViewer *file_viewer;
	Server *server;
	Cliente *cliente;
	bool mostrar_archivos_ocultos;

private:
	static Configuracion *instance;
};

#endif
