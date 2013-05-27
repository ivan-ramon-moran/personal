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
#include "Directorio.h"
#include "Configuracion.h"
#include "Mensaje.h"
#include "Archivo.h"
#include "DAutentificacion.h"
#include <thread>
#include <sqlite3.h>
#include "VentanaNuevoUsuario.h"
#include "BD.h"

using namespace std;

void AcercaDe();
void on_conectar_clicked();
void ThreadEscuchar();
bool ValidarConexion(string direccion, string str_puerto);
void EliminarArchivosOcultos(vector<Archivo> &v_archivos);
void EnviarDirectorios(string ruta);
void CargarBaseDeDatos();
void MostrarVentanaNuevoUsuario();

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
	GtkWidget *menu_servidor;
	GtkWidget *servidor;
	GtkWidget *agregar_usuario;
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
	GtkWidget *cont_detalles_archivo;
	GtkWidget *label_servidor;
	GtkWidget *img_info_barra_estado;
	GtkWidget *img_preview;
	GtkWidget *label_eti_nombre;
	GtkWidget *label_nombre;
	GtkWidget *cont_nombre;
	GtkWidget *label_eti_ruta;
	GtkWidget *label_ruta;
	GtkWidget *cont_ruta;
	GtkWidget *label_eti_tipo;
	GtkWidget *label_tipo;
	GtkWidget *cont_tipo;
	GtkWidget *label_eti_tamanyo;
	GtkWidget *label_tamanyo;
	GtkWidget *cont_tamanyo;

	CargarBaseDeDatos();
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	Configuracion::get_instance()->ventana_principal = window;
    gtk_window_set_position(GTK_WINDOW (window),GTK_WIN_POS_CENTER);
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
	menu_servidor = gtk_menu_new();

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

	//Menu servidor
	servidor = gtk_menu_item_new_with_label("Servidor");
	agregar_usuario = gtk_menu_item_new_with_label("Crear usuario");

	//Anyadimos el menu archivo
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(archivo), menu_archivo);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_archivo), conectar);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_archivo), salir);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), archivo);

	//Anyadimos el menu editar
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(editar), menu_editar);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_editar), preferencias);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), editar);

	//Menu servidor
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(servidor), menu_servidor);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_servidor), agregar_usuario);
	//gtk_menu_shell_append(GTK_MENU_SHELL(menu_archivo), salir);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), servidor);

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
	gtk_widget_set_name(GTK_WIDGET(combo_servidores), "combo_servidores");
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
	Configuracion::get_instance()->entry_direccion = entry_dir;
	Configuracion::get_instance()->entry_puerto = entry_puerto;
	Configuracion::get_instance()->boton_conectar = toolbar_conectar;
	Configuracion::get_instance()->estado = 1;

	//Señal del boton conectar de la toolbar.
	g_signal_connect (toolbar_conectar, "clicked", G_CALLBACK (on_conectar_clicked), NULL);
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(salir), "activate", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(acerca_de), "activate", G_CALLBACK(AcercaDe), NULL);
	g_signal_connect(G_OBJECT(agregar_usuario), "activate", G_CALLBACK(MostrarVentanaNuevoUsuario), NULL);
	//g_signal_connect(G_OBJECT(toolbar_conectar), "clicked", G_CALLBACK(on_conectar_clicked), file_viewer);

	//Posicionamos el visor de archivo
	cont_cuerpo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	//---------------------------CONTENEDOR DETALLES DE ARCHIVO-------------------------------------
	cont_detalles_archivo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_size_request(GTK_WIDGET(cont_detalles_archivo), 250, 0);
	gtk_box_pack_start(GTK_BOX(cont_cuerpo),cont_detalles_archivo, 0, 0, 0);

	//Creamos la imagen del preview del fichero o directorio
	img_preview = gtk_image_new_from_file("Images/preview/folder.png");
	//Creamos 2 labels y un contenedor para mostrar el nombre del fichero
	label_eti_nombre = gtk_label_new("Nombre: ");
	label_nombre = gtk_label_new("Ubuntu");
	cont_nombre = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	//Añadimos los labels
	gtk_box_pack_start(GTK_BOX(cont_nombre), GTK_WIDGET(label_eti_nombre), 0, 0, 20);
	gtk_box_pack_start(GTK_BOX(cont_nombre), GTK_WIDGET(label_nombre), 0, 0, 0);
	//Creamos 2 labels y un contenedor para mostrar la ruta del fichero
	label_eti_ruta = gtk_label_new("Ruta: ");
	label_ruta = gtk_label_new("/home/k3rnel/Escritorio");
	cont_ruta = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	//Añadimos los labels a su contenedor
	gtk_box_pack_start(GTK_BOX(cont_ruta), GTK_WIDGET(label_eti_ruta), 0, 0, 20);
	gtk_box_pack_start(GTK_BOX(cont_ruta), GTK_WIDGET(label_ruta), 0, 0, 20);
	//Creamos 2 labels para mostrar el tipo de fichero y su contenedor
	label_eti_tipo = gtk_label_new("Tipo: ");
	label_tipo = gtk_label_new("inode/directory");
	cont_tipo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	//Añadimos los labels a su contenedor
	gtk_box_pack_start(GTK_BOX(cont_tipo), GTK_WIDGET(label_eti_tipo), 0, 0, 20);
	gtk_box_pack_start(GTK_BOX(cont_tipo), GTK_WIDGET(label_tipo), 0, 0, 20);
	//Creamos 2 labels y su contenedor para mostrar el tamanyo de archivo
	label_eti_tamanyo = gtk_label_new("Tamaño: ");
	label_tamanyo = gtk_label_new("12 MB");
	cont_tamanyo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	//Añadimos los labels a su contenedor
	gtk_box_pack_start(GTK_BOX(cont_tamanyo), GTK_WIDGET(label_eti_tamanyo), 0, 0, 20);
	gtk_box_pack_start(GTK_BOX(cont_tamanyo), GTK_WIDGET(label_tamanyo), 0, 0, 0);

	//Añadimos todos los componentes graficos a la vista detalle de archivos/directorios
	gtk_box_pack_start(GTK_BOX(cont_detalles_archivo), GTK_WIDGET(img_preview), 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(cont_detalles_archivo), GTK_WIDGET(cont_nombre), 0, 0, 10);
	gtk_box_pack_start(GTK_BOX(cont_detalles_archivo), GTK_WIDGET(cont_ruta), 0, 0, 10);
	gtk_box_pack_start(GTK_BOX(cont_detalles_archivo), GTK_WIDGET(cont_tipo), 0, 0, 10);
	gtk_box_pack_start(GTK_BOX(cont_detalles_archivo), GTK_WIDGET(cont_tamanyo), 0, 0, 10);

	//Añadimos todos los componentes a la Configuracoin mediante punteros
	Configuracion::get_instance()->label_nombre = label_nombre;
	Configuracion::get_instance()->label_ruta = label_ruta;
	Configuracion::get_instance()->label_tipo = label_tipo;
	Configuracion::get_instance()->label_tamanyo = label_tamanyo;

	//----------------------------------------------------------------------------------------------

	//Creamos el visor de archivos
	FileViewer file_viewer(cont_cuerpo);
	//Metemos el file_viewer en la configuración
	Configuracion::get_instance()->file_viewer = &file_viewer;

	gtk_box_pack_start(GTK_BOX(contenedor), cont_cuerpo, 1, 1 ,10);

	Configuracion::get_instance()->file_viewer = &file_viewer;
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
	std::thread thread_escuchar(ThreadEscuchar);
	//----------------------------------------------------------------------------------------

	//------------------------------CLIENTE---------------------------------------------------
	Cliente cliente;
	Cliente *clientePtr = &cliente;
	Configuracion::get_instance()->cliente = clientePtr;
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

void on_conectar_clicked()
{
	string direccion, str_puerto, estado_autentificacion;;
	int puerto;
	GtkWidget *img_desconectar = gtk_image_new_from_file("Images/close.png");
	GtkWidget *img_conectar = gtk_image_new_from_file("Images/conectar.png");
	vector<Archivo> v_resultados;

	direccion = gtk_entry_get_text(GTK_ENTRY(Configuracion::get_instance()->entry_direccion));
	str_puerto = gtk_entry_get_text(GTK_ENTRY(Configuracion::get_instance()->entry_puerto));

	if (Configuracion::get_instance()->estado == 1)
	{
		if (ValidarConexion(direccion, str_puerto))
		{
			puerto = atoi(str_puerto.c_str());

			if (direccion != "" && str_puerto != "")
			{
				try
				{
					if (Configuracion::get_instance()->cliente->GetEstado() != "conectado")
					{
						DAutentificacion d_aut(Configuracion::get_instance()->ventana_principal);

						//Si el usuario ha pulsado aceptar en la ventana de autentificación, conectamos y mandamos los datos de autentificacion.
						if (Configuracion::get_instance()->usuario != "" && Configuracion::get_instance()->password != "")
						{
							//Conectamos al cliente y enviamos los datos de autentificacion
							Configuracion::get_instance()->cliente->Conectar(direccion, puerto);
							Configuracion::get_instance()->cliente->EnviarDatos(Configuracion::get_instance()->usuario);
							Configuracion::get_instance()->cliente->EnviarDatos(Configuracion::get_instance()->password);
							estado_autentificacion = Configuracion::get_instance()->cliente->RecibirDatos();

							if (estado_autentificacion == "AUT")
							{
								//Cambiamos el boton de conectar, a desconectar
								gtk_button_set_image(GTK_BUTTON(Configuracion::get_instance()->boton_conectar), img_desconectar);
								gtk_button_set_label(GTK_BUTTON(Configuracion::get_instance()->boton_conectar), "Desconectar");
								//Ponemos el estado de conexion a 0(Conectado).
								Configuracion::get_instance()->estado = 0;
								//Pedimos las rutas
								Configuracion::get_instance()->cliente->EnviarDatos("/");
								Configuracion::get_instance()->cliente->DeserializarObjeto(v_resultados);
								Configuracion::get_instance()->file_viewer->set_items(v_resultados);
							}
							else
							{
								//Mostramos un mensaje de error indicando fallo en la autentificacion.
								Mensaje mensaje("Error de autentificación", "No existe el usuario en la base de datos del servidor.", Configuracion::get_instance()->ventana_principal);
								Configuracion::get_instance()->estado = 1;
								Configuracion::get_instance()->cliente->Cerrar();
							}
						}
					}
				}
				catch (ExcepcionPersonalizada &e)
				{
					cout << e.what() << endl;
				}
			}
		}
		else
		{
			Mensaje mensaje("Error de conexión!", "Datos de conexión no validados. Debes rellenar los campos de conexion.", Configuracion::get_instance()->ventana_principal);
		}
	}
	else
	{
		//Si estamos conectados y le damos al boton de desconectar, desconectamos al cliente.
		Configuracion::get_instance()->cliente->Cerrar();
		//Volvemos a cambiar el boton de conectar a desconectar
		gtk_button_set_image(GTK_BUTTON(Configuracion::get_instance()->boton_conectar), img_conectar);
		gtk_button_set_label(GTK_BUTTON(Configuracion::get_instance()->boton_conectar), "Conectar");
		//Ponemos el estado a 1(Desconectado)
		Configuracion::get_instance()->estado = 1;
		//Borramos los items del visor de archivos
		Configuracion::get_instance()->file_viewer->eliminar_elementos();
	}
}


void ThreadEscuchar()
{
	string mensaje, usuario, password, sentencia;
	bool autentificado;
	Server server(7777);
	//Pasamos la direccion de memoria del campo estado de la barra de estado, para poder modificar
	//lo en el servidor.
	//server.SetLabelEstado(GTK_WIDGET(Configuracion::get_instance()->label_servidor));
	Configuracion::get_instance()->server = &server;

	while (1)
	{
		//Ponemos el server a escuchar!!!
		server.Escuchar();
		//Autentificación por parte del usuario
		usuario = server.RecibirDatos();
		password = server.RecibirDatos();
		//Comprobamos en la base de datos si existe el usuario
		sentencia = "SELECT * FROM usuarios WHERE usuario LIKE '"  + usuario + "' AND password LIKE '" + password + "'";
		autentificado = BD::ComprobarConsulta("NetTransfer.db", sentencia);

		if (autentificado)
			server.EnviarDatos("AUT");
		else
		{
			server.EnviarDatos("NO_AUT");
			mensaje = "salir";
		}
		//Realizamos la operacion pertinente
		while (mensaje != "salir" || server.GetEstadoCliente() != "desconectado")
		{
			//Recibimos la orden del cliente
			mensaje = server.RecibirDatos();
			if (mensaje != "salir")
				EnviarDirectorios(mensaje);
		}
	}
}

void gtk_main_quit()
{
	Configuracion::get_instance()->server->Close();
	if (Configuracion::get_instance()->estado == 0)
		Configuracion::get_instance()->cliente->Cerrar();
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


void EnviarDirectorios(string ruta)
{
	vector<string> v_resultados;
	vector<Archivo> v_archivos;
	GFile *file;
	GFileInfo *file_info;
	GError *error;
	const char *tipo_archivo;
	string str_tipo_archivo;
	unsigned long long file_size;

	Directorio::ListarDirectorio(ruta, v_resultados);

	for (unsigned int i = 0; i < v_resultados.size(); i++)
	{
		file_size = 0;
		//Obtenemos el mimetype del archivo
		file = g_file_new_for_path((ruta + "/" + v_resultados[i]).c_str());
		file_info = g_file_query_info(file, "standard::*", G_FILE_QUERY_INFO_NONE, NULL, &error);
		tipo_archivo = g_file_info_get_content_type (file_info);
		str_tipo_archivo = tipo_archivo;

		//Creamos un vector de objetos archivo para enviarlo al cliente
		if (str_tipo_archivo != "inode/directory")
		{
			Directorio::GetFileSize(ruta + "/" + v_resultados[i], file_size);
			Archivo archivo(v_resultados[i], ruta + "/", tipo_archivo, file_size);
			v_archivos.push_back(archivo);
		}
		else
		{
			Archivo archivo(v_resultados[i], ruta + "/", tipo_archivo, 0);
			v_archivos.push_back(archivo);
		}
	}

	//Si en la configuracion esta puesto que no mostremos archivos ocultos los eliminamos del vector
	if (!Configuracion::get_instance()->mostrar_archivos_ocultos)
		EliminarArchivosOcultos(v_archivos);

	//Enviamos los datos
	Configuracion::get_instance()->server->SerializarObjeto(v_archivos);
}

void CargarBaseDeDatos()
{
	sqlite3 *db;
	char *error;
	string sentencia;
	int res_ope;

	res_ope = sqlite3_open("NetTransfer.db", &db);
	sentencia = "CREATE TABLE usuarios (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, usuario TEXT NOT NULL, password TEXT NOT NULL)";
	res_ope = sqlite3_exec(db, sentencia.c_str(), NULL, NULL, &error);
	sentencia = "CREATE TABLE permisos (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, id_usuario INTEGER NOT NULL, directorio TEXT NOT NULL, lectura INTEGER NOT NULL, escritura INTEGER NOT NULL, FOREIGN KEY(id_usuario) REFERENCES usuarios(id))";
	res_ope = sqlite3_exec(db, sentencia.c_str(), NULL, NULL, &error);

	if (res_ope == SQLITE_OK)
			cout << "Operacion realizada" << endl;

	sentencia = "INSERT INTO usuarios (id, usuario, password) VALUES ('1', 'k3rnel', 'admin')";
	res_ope = sqlite3_exec(db, sentencia.c_str(), NULL, NULL, &error);

	if (res_ope == SQLITE_OK)
		cout << "Operacion realizada" << endl;

	sqlite3_close(db);
}

void MostrarVentanaNuevoUsuario()
{
	VentanaNuevoUsuario ventana(Configuracion::get_instance()->ventana_principal);
}
