/*
 * FileViewer.h
 *
 *  Created on: 17/05/2013
 *      Author: k3rnel
 */

#include "Configuracion.h"
#include <iostream>
#include <gtk/gtk.h>
#include <vector>
#include <sstream>
#include "Cliente.h"
#include "UtilidadesTipos.h"
#include "Pila.cpp"
#include "Archivo.h"

#ifndef FILEVIEWER_H_
#define FILEVIEWER_H_

using namespace std;

static Pila<string> rutas;

class FileViewer
{
	enum
	{
		COL_DISPLAY_NAME,
		COL_PIXBUF,
		NUM_COLS
	};

public:
	FileViewer();
	FileViewer(GtkWidget *contenedor_padre);

	//Operaciones permitidas
	void set_items(const vector<Archivo> &elementos);

private:
	//Contenedor donde pondremos el componente
	GtkWidget *contenedor_padre;
	//Visor de archivos y opciones
	GtkWidget *scrolled_window;
	GtkWidget *file_viewer;
	GtkWidget *cont_visor;
	GtkWidget *cont_bot_visor;
	GtkWidget *but_ord_arc;
	GtkWidget *but_ord_asc;
	GtkWidget *but_ord_del;
	GtkWidget *but_sub;
	GtkWidget *but_desc;
	GtkWidget *ev_bot_visor;
	GtkWidget *label_visor;
	GtkWidget *label_buscar;
	GtkWidget *entry_buscar;
	//Final del visor de archivos
	GtkWidget *label_num_archivos;
	GdkPixbuf *image_entry_buscar;
	GError *g;
	GtkWidget *ev_final_visor;
	GtkWidget *cont_final_visor;
	//Guardamos una referencia el cliente para poder llamar desde aqui a cualquier metodo del cliente

	//Vector que contendra los elementos a pintar en el file_viewer
	vector<Archivo> elementos;
	//Funciones auxiliares que el usuario no debe conocer.
	GtkTreeModel *create_and_fill_model ();
	void set_num_archivos(int num_archivos);

	//Señales (Cuidado han de ser static)
	static void on_item_activated (GtkTreeView *view, GtkTreePath *path, GtkTreeViewColumn *col, gpointer userdata);
	int ObtenerTipo(string tipo);
};

#endif /* FILEVIEWER_H_ */
