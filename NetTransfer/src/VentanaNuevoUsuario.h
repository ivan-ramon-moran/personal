#include <iostream>
#include <gtk/gtk.h>
#include "Configuracion.h"
#include "Mensaje.h"
#include "BD.h"
#include <gdk-pixbuf/gdk-pixbuf.h>
using namespace std;

#ifndef VENTANANUEVOUSUARIO_H_
#define VENTANANUEVOUSUARIO_H_

enum
{
	ITEM_RUTA = 0,
	ITEM_E,
	ITEM_L,
	N_COLUMNS
};

static void AbrirFileChooser();
static void AnyadirPermiso(GtkWidget *widget, gpointer lista);
static void ComprobarValidacion(GtkWidget *entry);
static void InsertarUsuario(GtkWidget *eidget, GtkTreeView *lista_permisos);

class VentanaNuevoUsuario
{
public:
	VentanaNuevoUsuario(GtkWidget *ventana_padre);
	virtual ~VentanaNuevoUsuario();

private :
	GtkWidget *ventana;
	GtkWidget *img_nuevo_usuario;
	GtkWidget *contenido;
	GtkWidget *contenedor_fixed;
	GtkWidget *label_nombre;
	GtkWidget *entry_nombre;
	GtkWidget *label_pass;
	GtkWidget *entry_pass;
	GtkWidget *img_importante, *img_importante2;
	GtkWidget *check_superusuario;
	GtkWidget *scroll_lista;
	GtkWidget *lista_permisos;
	GtkWidget *contenedor_botones;
	GtkWidget *boton_anyadir_usuario;
	GtkWidget *boton_cancelar;
	GtkWidget *check_permiso_l;
	GtkWidget *check_permiso_e;
	GtkWidget *boton_abrir_file_chooser;
	GtkWidget *boton_anyadir_permiso;
	GtkWidget *entry_directorio;
	GtkWidget *label_directorio;
};

#endif /* VENTANANUEVOUSUARIO_H_ */
