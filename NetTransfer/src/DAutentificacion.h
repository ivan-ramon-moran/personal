#include <iostream>
#include <gtk/gtk.h>
#include "Configuracion.h"

using namespace std;

#ifndef DAUTENTIFICACION_H_
#define DAUTENTIFICACION_H_

class DAutentificacion
{
public:
	DAutentificacion(GtkWidget *ventana_padre);
	virtual ~DAutentificacion();

private:
	GtkWidget *contenido;
	GtkWidget *label_usuario;
	GtkWidget *label_password;
	GtkWidget *cont_fixed;
	GtkWidget *img_password;
	GtkWidget *boton_aceptar;
	GtkWidget *boton_cancelar;
	GtkWidget *cont_botones;
	GtkWidget *ventana;
	GtkWidget *entry_usuario;
	GtkWidget *entry_password;

	static void on_boton_aceptar_clicked();
	static void on_boton_cancelar_clicked();

};

#endif /* DAUTENTIFICACION_H_ */
