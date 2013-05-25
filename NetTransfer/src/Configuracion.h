#ifndef CONF_H__
#define CONF_H__

#include <iostream>
#include "FileViewer.h"
#include "Cliente.h"
#include "Server.h"
#include <mutex>

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
	GtkWidget *ventana_principal;
	GtkWidget *ventana_aut;
	bool mostrar_archivos_ocultos;
	vector<Archivo> elementos;
	/*Punteros que hacen referencia a los componentes gráficos del visor de achivos para mostrar
	  los atributos de cada archivo/directorio*/
	GtkWidget *label_nombre, *label_ruta, *label_tipo, *label_tamanyo;

private:
	static Configuracion *instance;
};

#endif
