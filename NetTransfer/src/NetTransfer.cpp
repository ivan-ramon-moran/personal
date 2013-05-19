/*
 ============================================================================
 Name        : NetTransfer.cpp
 Author      : K 3 r N e L
 Version     :
 Copyright   : Free Software for free World!!!
 Description : FileTransfer program
 ============================================================================
 */

#include <gtk/gtk.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "FileViewer.h"
#include "Server.h"
#include <pthread.h>
#include "Cliente.h"
#include <pthread.h>
#include "Directorio.h"
#include "Configuracion.h"
#include "Mensaje.h"
#include "Archivo.h"

using namespace std;

struct InfoConexion
{
	GtkWidget *entry_direccion;
	GtkWidget *entry_puerto;
	Cliente *cliente;
	GtkWidget *button_conectar;
	FileViewer *file_viewer;
	GtkWidget *label_servidor;
	GtkWidget *ventana_principal;
	//0 para conectado y 1 para desconectado
	int estado;
};

struct CompartirConThreads
{
	Server *server;
	GtkWidget *label_servidor;
	Cliente *cliente;
};

CompartirConThreads data_threads;

void Imprimir(GtkWidget *widget, gpointer *callback_data);
void AcercaDe();
void on_conectar_clicked(GtkWidget *widget, InfoConexion* c);
void *Escuchar(void *threadid);
bool ValidarConexion(string direccion, string str_puerto);
void EliminarArchivosOcultos(vector<Archivo> &v_archivos);

int main (int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *toolbar_conectar;
	GtkWidget *contenedor;
	GtkWidget *toolbar;
	GtkWidget *imagen_conectar;
	GtkWidget *toolbar_explorar;
	GtkWidget *imagen_explorar;
	GtkWidget *toolbar_transferencias;
	GtkWidget *toolbar_servidor;
	GtkWidget *imagen_servidor;
	GtkWidget *imagen_transferencias;
	GtkCssProvider *provider;
	GdkDisplay *display;
	GdkScreen *screen;
	//Para poder pintar la toolbar ya que por si sola no contiene fondo.
	GtkWidget *ev_toolbar;
	GtkWidget *ev_datos_con;
	GtkWidget *cont_datos_con;
	//Creamos el menu
	GtkWidget *menubar;
	GtkWidget *menu_archivo;
	GtkWidget *archivo;
	GtkWidget *conectar;
	GtkWidget *salir;
	GtkWidget *menu_editar;
	GtkWidget *preferencias;
	GtkWidget *editar;
	GtkWidget *menu_ayuda;
	GtkWidget *ayuda;
	GtkWidget *acerca_de;
	//Entry de conexion
	GtkWidget *entry_dir;
	GtkWidget *entry_puerto;
	GtkWidget *label_dir;
	GtkWidget *label_puerto;
	GtkWidget *combo_servidores;
	GtkWidget *label_con_rapidas;
	//Barra de estado
	GtkWidget *barra_estado;
	GtkWidget *ev_barra_estado;
	GtkWidget *separador_con;
	GtkWidget *toolbar_chat;
	GtkWidget *imagen_chat;
	GtkWidget *cont_cuerpo;
	GtkWidget *iz_borrar;
	GtkWidget *label_servidor;
	GtkWidget *img_info_barra_estado;

	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	InfoConexion *info_conexion = new InfoConexion;
	info_conexion->ventana_principal = window;
	gtk_widget_set_name(GTK_WIDGET(window), "vent_principal");
	gtk_window_set_default_size(GTK_WINDOW(window),1000, 600);
	gtk_window_set_title(GTK_WINDOW(window), "NetTransfer - Share your files!!!");

	//Creamos el contenedor y lo anyadimos
	contenedor = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
	gtk_widget_set_name(GTK_WIDGET(toolbar), "toolbar");
	ev_toolbar = gtk_event_box_new();

	//CSS Provider
	/*---------------- CSS ----------------------------------------------------------------------------------------------------*/
	provider = gtk_css_provider_new ();
	display = gdk_display_get_default ();
	screen = gdk_display_get_default_screen (display);
	gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	gsize bytes_written, bytes_read;

	const gchar* home = "style.css";  // your path, for instance: /home/zerohour/Documents/programming/cssexternal.css

	GError *error = 0;

	gtk_css_provider_load_from_path (provider, g_filename_to_utf8(home, strlen(home), &bytes_read, &bytes_written, &error), NULL);
	g_object_unref (provider);
	  /*-------------------------------------------------------------------------------------------------------------------------*/

	//Creamos el menubar y los menus
	menubar = gtk_menu_bar_new();
	menu_archivo = gtk_menu_new();
	menu_editar = gtk_menu_new();
	menu_ayuda = gtk_menu_new();

	//Menu archivo
	archivo = gtk_menu_item_new_with_label("Archivo");
	conectar = gtk_menu_item_new_with_label("Conectar con...");
	salir = gtk_menu_item_new_with_label("Salir");

	//Menu editar
	editar = gtk_menu_item_new_with_label("Editar");
	preferencias = gtk_menu_item_new_with_label("Preferencias");

	//Menu ayuda
	ayuda = gtk_menu_item_new_with_label("Ayuda");
	acerca_de = gtk_menu_item_new_with_label("Acerca de...");

	//Anyadimos el menu archivo
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(archivo), menu_archivo);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_archivo), conectar);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_archivo), salir);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), archivo);

	//Anyadimos el menu editar
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(editar), menu_editar);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_editar), preferencias);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), editar);

	//Anyadimos el menu ayuda
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(ayuda), menu_ayuda);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_ayuda), acerca_de);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), ayuda);

	//Anyadimos el contenedor y el menu al contenedor de la ventana
	gtk_container_add(GTK_CONTAINER(contenedor), menubar);
	gtk_container_add(GTK_CONTAINER(window), contenedor);

	//Anyadimos la toolbar y los botones
	//Boton conectar
	gtk_container_add(GTK_CONTAINER(ev_toolbar), toolbar);
	gtk_container_add(GTK_CONTAINER(contenedor), GTK_WIDGET(ev_toolbar));
	gtk_widget_set_name(GTK_WIDGET(ev_toolbar), "toolbar");
	imagen_conectar = gtk_image_new_from_file("Images/conectar.png");
	toolbar_conectar = gtk_button_new_with_label("Conectar");
	gtk_widget_set_size_request(GTK_WIDGET(toolbar_conectar), 70, 70);
	gtk_button_set_alignment(GTK_BUTTON(toolbar_conectar), 0.5, 0.9);
	gtk_button_set_image(GTK_BUTTON(toolbar_conectar), imagen_conectar);
	gtk_button_set_image_position(GTK_BUTTON(toolbar_conectar), GTK_POS_TOP);
	gtk_widget_set_name(GTK_WIDGET(toolbar_conectar), "toolbar_button");
	gtk_button_set_relief(GTK_BUTTON(toolbar_conectar), GTK_RELIEF_NONE);

	//Boton explorar
	toolbar_explorar = gtk_button_new_with_label("Explorar");
	gtk_button_set_alignment(GTK_BUTTON(toolbar_explorar), 0.5, 0.9);
	gtk_button_set_image_position(GTK_BUTTON(toolbar_explorar), GTK_POS_TOP);
	gtk_widget_set_size_request(GTK_WIDGET(toolbar_explorar), 70, 70);
	imagen_explorar = gtk_image_new_from_file("Images/explorar.png");
	gtk_button_set_image(GTK_BUTTON(toolbar_explorar), imagen_explorar);
	gtk_widget_set_name(GTK_WIDGET(toolbar_explorar), "toolbar_button");
	gtk_button_set_relief(GTK_BUTTON(toolbar_explorar), GTK_RELIEF_NONE);

	//Boton transferencias
	toolbar_transferencias = gtk_button_new_with_label("Transferencias");
	gtk_button_set_alignment(GTK_BUTTON(toolbar_transferencias), 0.5, 0.9);
	imagen_transferencias = gtk_image_new_from_file("Images/transferencias.png");
	gtk_button_set_image(GTK_BUTTON(toolbar_transferencias), imagen_transferencias);
	gtk_button_set_image_position(GTK_BUTTON(toolbar_transferencias), GTK_POS_TOP);
	gtk_widget_set_name(GTK_WIDGET(toolbar_transferencias), "toolbar_button");
	gtk_button_set_relief(GTK_BUTTON(toolbar_transferencias), GTK_RELIEF_NONE);

	//Boton servidor
	toolbar_servidor = gtk_button_new_with_label("Servidor");
	gtk_button_set_alignment(GTK_BUTTON(toolbar_servidor), 0.5, 0.9);
	imagen_servidor = gtk_image_new_from_file("Images/toolbar_server.png");
	gtk_button_set_image(GTK_BUTTON(toolbar_servidor), imagen_servidor);
	gtk_button_set_image_position(GTK_BUTTON(toolbar_servidor), GTK_POS_TOP);
	gtk_widget_set_name(GTK_WIDGET(toolbar_servidor), "toolbar_button");
	gtk_button_set_relief(GTK_BUTTON(toolbar_servidor), GTK_RELIEF_NONE);

	//Boton chat
	toolbar_chat = gtk_button_new_with_label("Chat");
	gtk_button_set_alignment(GTK_BUTTON(toolbar_chat), 0.5, 0.9);
	imagen_chat = gtk_image_new_from_file("Images/chat.png");
	gtk_button_set_image(GTK_BUTTON(toolbar_chat), imagen_chat);
	gtk_button_set_image_position(GTK_BUTTON(toolbar_chat), GTK_POS_TOP);
	gtk_widget_set_name(GTK_WIDGET(toolbar_chat), "toolbar_button");
	gtk_button_set_relief(GTK_BUTTON(toolbar_chat), GTK_RELIEF_NONE);

	gtk_box_pack_start(GTK_BOX(toolbar), GTK_WIDGET(toolbar_conectar), false, false, 3);
	gtk_container_add(GTK_CONTAINER(toolbar), toolbar_explorar);
	gtk_container_add(GTK_CONTAINER(toolbar), toolbar_transferencias);
	gtk_container_add(GTK_CONTAINER(toolbar), toolbar_servidor);
	gtk_container_add(GTK_CONTAINER(toolbar), toolbar_chat);

	//Creamos el contenedor de los datos de conexion
	cont_datos_con = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	ev_datos_con = gtk_event_box_new();

	label_dir = gtk_label_new("Dirección IP: ");
	entry_dir = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(entry_dir), "127.0.0.1");
	gtk_entry_set_alignment(GTK_ENTRY(entry_dir), 0.5);
	gtk_widget_set_name(GTK_WIDGET(entry_dir), "entry_conexion");

	label_puerto = gtk_label_new("Puerto: ");
	entry_puerto = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(entry_puerto), "7777");
	gtk_entry_set_alignment(GTK_ENTRY(entry_puerto), 0.5);
	gtk_widget_set_name(GTK_WIDGET(entry_puerto), "entry_conexion");

	label_con_rapidas = gtk_label_new("Conexiones rápidas: ");
	combo_servidores = gtk_combo_box_text_new();
	gtk_widget_set_size_request(GTK_WIDGET(combo_servidores), 150, 25);
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_servidores),"Casa", "Casa");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_servidores),"Oficina", "Oficina");

	//Añadimos todos los componentes de conexion
	gtk_box_pack_start(GTK_BOX(cont_datos_con), GTK_WIDGET(label_dir), false, false, 10);
	gtk_container_add(GTK_CONTAINER(cont_datos_con), entry_dir);
	gtk_container_add(GTK_CONTAINER(cont_datos_con), label_puerto);
	gtk_container_add(GTK_CONTAINER(cont_datos_con), entry_puerto);
	gtk_container_add(GTK_CONTAINER(cont_datos_con), label_con_rapidas);
	gtk_container_add(GTK_CONTAINER(cont_datos_con), combo_servidores);

	//Creamos el eventbox que contendra al contenedor de los datos de conexion
	gtk_container_add(GTK_CONTAINER(ev_datos_con), cont_datos_con);
	gtk_widget_set_name(GTK_WIDGET(ev_datos_con), "datos_conexion");
	gtk_container_add(GTK_CONTAINER(contenedor), ev_datos_con);

	//Separado entre la toolbar y el contenido
	separador_con = gtk_event_box_new();
	gtk_widget_set_size_request(GTK_WIDGET(separador_con), 0, 5);
	gtk_container_add(GTK_CONTAINER(contenedor), separador_con);
	gtk_widget_set_name(GTK_WIDGET(separador_con), "separador_con");

	//Creamos el struct para pasar los datos de conexion a conectar.
	info_conexion->entry_direccion = entry_dir;
	info_conexion->entry_puerto = entry_puerto;
	info_conexion->button_conectar = toolbar_conectar;
	info_conexion->estado = 1;

	//Señal del boton conectar de la toolbar.
	g_signal_connect (toolbar_conectar, "clicked", G_CALLBACK (on_conectar_clicked), info_conexion);
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(salir), "activate", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(acerca_de), "activate", G_CALLBACK(AcercaDe), NULL);
	//g_signal_connect(G_OBJECT(toolbar_conectar), "clicked", G_CALLBACK(on_conectar_clicked), file_viewer);

	//Posicionamos el visor de archivo
	cont_cuerpo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	//BORRAR ESTO CUANDO TENGAMOS CONTENIDO
	iz_borrar = gtk_event_box_new();
	gtk_widget_set_size_request(GTK_WIDGET(iz_borrar), 250, 0);
	gtk_box_pack_start(GTK_BOX(cont_cuerpo),iz_borrar, 0, 0, 0);

	//Creamos el visor de archivos
	FileViewer file_viewer(cont_cuerpo);
	//Metemos el file_viewer en la configuración
	Configuracion::get_instance()->file_viewer = &file_viewer;

	gtk_box_pack_start(GTK_BOX(contenedor), cont_cuerpo, 1, 1 ,10);

	info_conexion->file_viewer = &file_viewer;
	//----------------------------------------------------------------------------------------------

	//Creamos la barra de estado y la anyadimos
	barra_estado = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	label_servidor = gtk_label_new("Esperando conexiones...");
	img_info_barra_estado = gtk_image_new_from_file("Images/info.png");
	gtk_widget_set_size_request(GTK_WIDGET(barra_estado), 0, 30);
	ev_barra_estado = gtk_event_box_new();
	gtk_widget_set_name(GTK_WIDGET(ev_barra_estado), "barra_estado");
	gtk_box_pack_start(GTK_BOX(barra_estado), img_info_barra_estado, 0, 0, 10);
	gtk_box_pack_start(GTK_BOX(barra_estado), label_servidor, 0, 0, 0);
	gtk_container_add(GTK_CONTAINER(ev_barra_estado), barra_estado);
	gtk_container_add(GTK_CONTAINER(contenedor), ev_barra_estado);

	gtk_widget_show_all(window);

	//-----------------------------INICIO SERVER----------------------------------------------
	pthread_t thread_escuchar;
	pthread_create(&thread_escuchar, NULL, Escuchar, (void *)&label_servidor);
	//----------------------------------------------------------------------------------------

	//------------------------------CLIENTE---------------------------------------------------
	Cliente cliente;
	Cliente *clientePtr = &cliente;
	info_conexion->cliente = clientePtr;
	data_threads.label_servidor = label_servidor;
	//----------------------------------------------------------------------------------------

	gtk_main();
}

void Imprimir(GtkWidget *widget, gpointer callback_data)
{
	const gchar *text;

	text = gtk_entry_get_text(GTK_ENTRY(callback_data));

	cout << text << endl;
}

void AcercaDe()
{
	cout << "Menu item acerca de seleccionado" << endl;
}

void on_conectar_clicked(GtkWidget *widget, InfoConexion *info)
{
	string direccion, str_puerto;
	int puerto;
	GtkWidget *img_desconectar = gtk_image_new_from_file("Images/close.png");
	GtkWidget *img_conectar = gtk_image_new_from_file("Images/conectar.png");
	vector<Archivo> v_resultados;

	direccion = gtk_entry_get_text(GTK_ENTRY(info->entry_direccion));
	str_puerto = gtk_entry_get_text(GTK_ENTRY(info->entry_puerto));

	if (info->estado == 1)
	{
		if (ValidarConexion(direccion, str_puerto))
		{
			puerto = atoi(str_puerto.c_str());

			if (direccion != "" && str_puerto != "")
			{
				try
				{
					if (info->cliente->GetEstado() != "conectado")
						info->cliente->Conectar(direccion, puerto);

					//data_threads.cliente = info->cliente;
					Configuracion::get_instance()->cliente = info->cliente;
				}
				catch (ExcepcionPersonalizada &e)
				{
					cout << e.what() << endl;
				}

				//Cambiamos el boton de conectar, a desconectar
				gtk_button_set_image(GTK_BUTTON(info->button_conectar), img_desconectar);
				gtk_button_set_label(GTK_BUTTON(info->button_conectar), "Desconectar");
				//Ponemos el estado de conexion a 0(Conectado).
				info->estado = 0;
				//Pedimos las rutas
				info->cliente->EnviarDatos("/");
				info->cliente->DeserializarObjeto(v_resultados);
				info->file_viewer->set_items(v_resultados);

			}
		}
		else
		{
			Mensaje mensaje("Error de conexión!", "Datos de conexión no validados. Debes rellenar los campos de conexion.", info->ventana_principal);
		}
	}
	else
	{
		//Si estamos conectados y le damos al boton de desconectar, desconectamos al cliente.
		info->cliente->Cerrar();
		//Volvemos a cambiar el boton de desconectar a desconectar
		gtk_button_set_image(GTK_BUTTON(info->button_conectar), img_conectar);
		gtk_button_set_label(GTK_BUTTON(info->button_conectar), "Conectar");
		//Ponemos el estado a 1(Desconectato)
		info->estado = 1;
	}
}


void *Escuchar(void *info)
{
	string mensaje;
	vector<string> v_resultados;
	vector<Archivo> v_archivos;
	GFile *file;
	GFileInfo *file_info;
	GError *error;
	const char *tipo_archivo;

	Server server(7777);
	//Pasamos la direccion de memoria del campo estado de la barra de estado, para poder modificar
	//lo en el servidor.
	server.SetLabelEstado(GTK_WIDGET(data_threads.label_servidor));

	while (1)
	{
		//Ponemos el server a escuchar!!!
		server.Escuchar();

		//Recibimos el mensaje de cliente
		mensaje = server.RecibirDatos();

		//Realizamos la operacion pertinente
		while (mensaje != "salir" || server.GetEstadoCliente() != "desconectado")
		{
			cout << "El mensaje es: " << mensaje << endl;
			cout << "Longitud: " << mensaje.length() << endl;

			try
			{
				Directorio::ListarDirectorio(mensaje, v_resultados);
				cout << "gadfsñkhhdscdsgfu" << endl;
			}
			catch (exception &e)
			{
				cout << "ERROR!!!" << endl;
			}

			//v_archivos.clear();

			for (unsigned int i = 0; i < v_resultados.size(); i++)
			{
				//Obtenemos el mimetype del archivo
				file = g_file_new_for_path((mensaje + "/" + v_resultados[i]).c_str());
				file_info = g_file_query_info(file, "standard::*", G_FILE_QUERY_INFO_NONE, NULL, &error);
				tipo_archivo = g_file_info_get_content_type (file_info);
				//Creamos un vector de objetos archivo para enviarlo al cliente
				Archivo archivo(v_resultados[i], mensaje + "/", tipo_archivo, 0);
				//cout << tipo_archivo << endl;
				v_archivos.push_back(archivo);
			}

			//Si en la configuracion esta puesto que no mostremos archivos ocultos los eliminamos del vector
			if (!Configuracion::get_instance()->mostrar_archivos_ocultos)
				EliminarArchivosOcultos(v_archivos);

			//Limpiamos el mensaje
			mensaje.clear();
			//Enviamos los datos
			server.SerializarObjeto(v_archivos);

			//Esperamos otra comunicacion del cliente
			mensaje = server.RecibirDatos();
		}
	}

	return 0;
}

void gtk_main_quit()
{
	data_threads.server->Close();
}

bool ValidarConexion(string direccion, string str_puerto)
{
	int contador_puntos = 0, octeto, puerto;
	string str_octeto;
	bool en_rango = true, correcta = false;

	for (unsigned int i = 0; i < direccion.length() && en_rango; i++)
	{
		if (direccion[i] == '.')
		{
			octeto = atoi(str_octeto.c_str());

			if (octeto > 255)
				en_rango = false;

			contador_puntos++;
			str_octeto = "";
		}
		str_octeto += direccion[i];
	}

	puerto = atoi(str_puerto.c_str());

	if (en_rango && contador_puntos == 3 && puerto < 65535)
		correcta = true;

	return correcta;
}

void EliminarArchivosOcultos(vector<Archivo> &v_archivos)
{
	for (unsigned int i = 0; i < v_archivos.size(); i++)
	{
		if (v_archivos[i].get_nombre()[0] == '.')
		{
			v_archivos[i] = v_archivos.back();
			v_archivos.pop_back();
			i--;
		}
	}
}
