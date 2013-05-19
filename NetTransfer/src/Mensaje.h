/*
 * Esta clase sirve para mostrar al usuario ventanas con informacion como
 * puede ser: errores, informacion etc...
 */

#include <iostream>
#include <gtk/gtk.h>

using namespace std;

#ifndef MENSAJE_H_
#define MENSAJE_H_

static GtkWidget *ventana;
static void cerrar_ventana();

class Mensaje
{
public:
	Mensaje();
	Mensaje(string titulo ,string mensaje, GtkWidget *ventana_padre);

private:
	GtkWidget *label_mensaje;
	GtkWidget *cont_contenido;
	GtkWidget *action_area;
	GtkWidget *boton_cerrar;
	GtkWidget *img_error;
	GtkWidget *cont_mensaje;
	GtkWidget *img_cerrar;
};

#endif /* MENSAJE_H_ */
