#include "Mensaje.h"

Mensaje::Mensaje() {}

Mensaje::Mensaje(string titulo, string mensaje, GtkWidget *ventana_padre)
{

	ventana = gtk_dialog_new_with_buttons(  titulo.c_str(),
            								GTK_WINDOW( ventana_padre ),
            								GTK_DIALOG_DESTROY_WITH_PARENT,
            								NULL,
            								NULL );

	//Creamos el mensaje y la imagen de error
	label_mensaje = gtk_label_new(mensaje.c_str());
	img_error = gtk_image_new_from_file("Images/dialog_error.png");

	//Creamos el hbox del mensaje y la imagen de error, informacion etc...
	cont_mensaje = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(cont_mensaje), GTK_WIDGET(img_error), 0, 0, 20);
	gtk_box_pack_start(GTK_BOX(cont_mensaje), GTK_WIDGET(label_mensaje), 0, 0, 20);

	cont_contenido = gtk_dialog_get_content_area(GTK_DIALOG(ventana));
	action_area = gtk_dialog_get_action_area(GTK_DIALOG(ventana));
	boton_cerrar = gtk_button_new_with_label("Cerrar");
	img_cerrar = gtk_image_new_from_file("Images/delete.png");
	gtk_button_set_image(GTK_BUTTON(boton_cerrar), GTK_WIDGET(img_cerrar));

	gtk_window_set_decorated(GTK_WINDOW(ventana), 1);
	gtk_widget_set_name(GTK_WIDGET(ventana), "ventana_mensaje");
	gtk_widget_set_size_request(GTK_WIDGET(ventana), 450, 110);
	gtk_box_pack_start(GTK_BOX(cont_contenido), GTK_WIDGET(cont_mensaje), 0, 0, 20);
	//gtk_box_pack_start(GTK_BOX(cont_contenido), GTK_WIDGET(label_mensaje), 0, 0, 30);
	gtk_box_pack_start(GTK_BOX(action_area), GTK_WIDGET(boton_cerrar), 0, 0, 0);

	g_signal_connect(G_OBJECT(boton_cerrar), "clicked", cerrar_ventana, NULL);

	gtk_widget_show_all(ventana);

	gtk_dialog_run(GTK_DIALOG(ventana));
}

void cerrar_ventana()
{
	gtk_widget_destroy(ventana);
}
