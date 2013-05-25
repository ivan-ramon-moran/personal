/*
 * DAutentificacion.cpp
 *
 *  Created on: 25/05/2013
 *      Author: k3rnel
 */

#include "DAutentificacion.h"

DAutentificacion::DAutentificacion(GtkWidget *ventana_padre)
{
	ventana = gtk_dialog_new_with_buttons(  "Autentificacion",
	            							GTK_WINDOW(ventana_padre ),
	            							GTK_DIALOG_DESTROY_WITH_PARENT,
	            							NULL,
	            							NULL);
	Configuracion::get_instance()->ventana_aut = ventana;
	gtk_widget_set_name(GTK_WIDGET(ventana), "ventana_aut");
	contenido = gtk_dialog_get_content_area(GTK_DIALOG(ventana));
	//gtk_window_set_modal(GTK_WINDOW(ventana), 1);
	gtk_window_set_decorated(GTK_WINDOW(ventana), 1);
	gtk_widget_set_size_request(GTK_WIDGET(ventana), 420, 150);
	cont_fixed = gtk_fixed_new();
	img_password = gtk_image_new_from_file("Images/password.png");

	//Creamos el componentes del usuario
	label_usuario = gtk_label_new("Usuario: ");
	entry_usuario = gtk_entry_new();
	gtk_widget_set_name(GTK_WIDGET(entry_usuario), "entry_usuario");
	//Creamos el componentes del password
	label_password = gtk_label_new("Contraseña: ");
	entry_password = gtk_entry_new();
	gtk_widget_set_name(GTK_WIDGET(entry_password), "entry_password");
	//Añadimos los componentes al contenedor principal de la ventana
	gtk_fixed_put(GTK_FIXED(cont_fixed), GTK_WIDGET(img_password), 10, 15);
	gtk_fixed_put(GTK_FIXED(cont_fixed), GTK_WIDGET(label_usuario), 150, 50);
	gtk_fixed_put(GTK_FIXED(cont_fixed), GTK_WIDGET(entry_usuario), 230, 45);
	gtk_fixed_put(GTK_FIXED(cont_fixed), GTK_WIDGET(label_password), 150, 90);
	gtk_fixed_put(GTK_FIXED(cont_fixed), GTK_WIDGET(entry_password), 230, 85);
	gtk_container_add(GTK_CONTAINER(contenido), GTK_WIDGET(cont_fixed));
	//Añadimos los botones
	cont_botones = gtk_dialog_get_action_area(GTK_DIALOG(ventana));
	boton_aceptar = gtk_button_new_with_label("Aceptar");
	boton_cancelar = gtk_button_new_with_label("Cancelar");
	gtk_container_add(GTK_CONTAINER(cont_botones), GTK_WIDGET(boton_aceptar));
	gtk_container_add(GTK_CONTAINER(cont_botones), GTK_WIDGET(boton_cancelar));
	//Conectamos las señales
	g_signal_connect(G_OBJECT(boton_aceptar), "clicked", G_CALLBACK(on_boton_aceptar_clicked), NULL);

	gtk_widget_show_all(ventana);

	gtk_dialog_run(GTK_DIALOG(ventana));
}

DAutentificacion::~DAutentificacion() {
	// TODO Auto-generated destructor stub
}


void DAutentificacion::on_boton_aceptar_clicked()
{
	gtk_widget_hide(GTK_WIDGET(Configuracion::get_instance()->ventana_aut));
}
