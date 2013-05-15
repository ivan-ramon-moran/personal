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

using namespace std;

enum
{
  COL_DISPLAY_NAME,
  COL_PIXBUF,
  NUM_COLS
};

void Imprimir(GtkWidget *widget, gpointer callback_data);
void AcercaDe();
GtkTreeModel *create_and_fill_model ();
void on_item_activated (GtkTreeView *view, GtkTreePath *path, GtkTreeViewColumn *col, gpointer userdata);
void on_conectar_clicked(GtkWidget *widget, gpointer c);

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
	GtkWidget *file_viewer;
	GtkWidget *scrolled_window;
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
	//Visor de archivos y opciones
	GtkWidget *cont_cuerpo;
	GtkWidget *iz_borrar;
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
	GtkWidget *ev_final_visor;
	GtkWidget *label_num_archivos;
	GtkWidget *cont_final_visor;
	GdkPixbuf *image_entry_buscar;
	GError *g = NULL;
	GtkWidget *toolbar_chat;
	GtkWidget *imagen_chat;

	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
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
	gtk_entry_set_alignment(GTK_ENTRY(entry_dir), 0.5);
	gtk_widget_set_name(GTK_WIDGET(entry_dir), "entry_conexion");

	label_puerto = gtk_label_new("Puerto: ");
	entry_puerto = gtk_entry_new();
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

	//Cremos el visor de archivos
	file_viewer = gtk_icon_view_new_with_model(create_and_fill_model());
	cout << file_viewer << endl;
	gtk_icon_view_set_text_column (GTK_ICON_VIEW (file_viewer), COL_DISPLAY_NAME);
	gtk_icon_view_set_pixbuf_column (GTK_ICON_VIEW (file_viewer), COL_PIXBUF);
	gtk_icon_view_set_selection_mode (GTK_ICON_VIEW (file_viewer), GTK_SELECTION_MULTIPLE);

	//Creamos el area de scroll
	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolled_window), GTK_SHADOW_IN);


	//g_signal_connect (toolbar_conectar, "clicked", G_CALLBACK (Imprimir), entry);
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(salir), "activate", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(acerca_de), "activate", G_CALLBACK(AcercaDe), NULL);
	g_signal_connect(G_OBJECT(file_viewer), "item-activated", G_CALLBACK(on_item_activated), NULL);
	g_signal_connect(G_OBJECT(toolbar_conectar), "clicked", G_CALLBACK(on_conectar_clicked), file_viewer);
	//--------------------------------------BOTONERA Y CABECERA VISOR DE ARCHIVOS--------------------
	ev_bot_visor = gtk_event_box_new();
	cont_visor = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	cont_bot_visor = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_add(GTK_CONTAINER(ev_bot_visor), cont_bot_visor);
	gtk_widget_set_size_request(GTK_WIDGET(ev_bot_visor), 0, 25);
	gtk_widget_set_name(GTK_WIDGET(ev_bot_visor), "botonera_visor");
	gtk_container_add(GTK_CONTAINER(cont_visor), ev_bot_visor);
	gtk_box_pack_start(GTK_BOX(cont_visor), scrolled_window, 1, 1, 0);

	//Botones del visor
	but_ord_arc = gtk_button_new();
	gtk_box_pack_start(GTK_BOX(cont_bot_visor), but_ord_arc, 0, 0, 0);
	gtk_widget_set_name(GTK_WIDGET(but_ord_arc), "bot_visor");
	GtkWidget *img_but_ord;
	img_but_ord = gtk_image_new_from_file("Images/ord_des.png");
	gtk_button_set_image(GTK_BUTTON(but_ord_arc),img_but_ord);
	gtk_button_set_relief(GTK_BUTTON(but_ord_arc), GTK_RELIEF_NONE);
	gtk_widget_set_size_request(GTK_WIDGET(but_ord_arc), 27, 0);

	but_ord_asc = gtk_button_new();
	gtk_box_pack_start(GTK_BOX(cont_bot_visor), but_ord_asc, 0, 0, 0);
	gtk_widget_set_name(GTK_WIDGET(but_ord_asc), "bot_visor");
	GtkWidget *img_but_asc;
	img_but_asc = gtk_image_new_from_file("Images/ord_asc.png");
	gtk_button_set_image(GTK_BUTTON(but_ord_asc),img_but_asc);
	gtk_button_set_relief(GTK_BUTTON(but_ord_asc), GTK_RELIEF_NONE);
	gtk_widget_set_size_request(GTK_WIDGET(but_ord_asc), 27, 0);

	but_ord_del = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(cont_bot_visor), but_ord_del);
	gtk_widget_set_name(GTK_WIDGET(but_ord_del), "bot_visor");
	GtkWidget *img_but_del;
	img_but_del = gtk_image_new_from_file("Images/delete.png");
	gtk_button_set_image(GTK_BUTTON(but_ord_del),img_but_del);
	gtk_button_set_relief(GTK_BUTTON(but_ord_del), GTK_RELIEF_NONE);
	gtk_widget_set_size_request(GTK_WIDGET(but_ord_del), 27, 0);

	but_sub = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(cont_bot_visor), but_sub);
	gtk_widget_set_name(GTK_WIDGET(but_sub), "bot_visor");
	GtkWidget *img_but_sub;
	img_but_sub = gtk_image_new_from_file("Images/subir.png");
	gtk_button_set_image(GTK_BUTTON(but_sub),img_but_sub);
	gtk_button_set_relief(GTK_BUTTON(but_sub), GTK_RELIEF_NONE);
	gtk_widget_set_size_request(GTK_WIDGET(but_sub), 27, 0);

	but_desc = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(cont_bot_visor), but_desc);
	gtk_widget_set_name(GTK_WIDGET(but_desc), "bot_visor");
	GtkWidget *img_but_desc;
	img_but_desc = gtk_image_new_from_file("Images/desc.png");
	gtk_button_set_image(GTK_BUTTON(but_desc),img_but_desc);
	gtk_button_set_relief(GTK_BUTTON(but_desc), GTK_RELIEF_NONE);
	gtk_widget_set_size_request(GTK_WIDGET(but_desc), 27, 0);

	//Label del visor de archivos
	label_visor = gtk_label_new("Visor de archivos");
	gtk_box_pack_start(GTK_BOX(cont_bot_visor), label_visor, 1, 1, 0);

	//Label y entry buscar
	label_buscar = gtk_label_new("Buscar: ");
	entry_buscar = gtk_entry_new();
	image_entry_buscar = gdk_pixbuf_new_from_file("Images/search.png", &g);
	gtk_entry_set_icon_from_pixbuf(GTK_ENTRY(entry_buscar), GTK_ENTRY_ICON_PRIMARY, image_entry_buscar);
	gtk_widget_set_name(GTK_WIDGET(entry_buscar), "entry_buscar");
	gtk_box_pack_start(GTK_BOX(cont_bot_visor), label_buscar, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(cont_bot_visor), entry_buscar, 0, 0, 0);

	//Posicionamos el visor de archivo
	cont_cuerpo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	//BORRAR ESTO CUANDO TENGAMOS CONTENIDO
	iz_borrar = gtk_event_box_new();
	gtk_widget_set_size_request(GTK_WIDGET(iz_borrar), 250, 0);
	gtk_box_pack_start(GTK_BOX(cont_cuerpo),iz_borrar, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(cont_cuerpo),cont_visor, 1, 1, 10);

	gtk_container_add (GTK_CONTAINER (scrolled_window), file_viewer);
	gtk_widget_set_name(GTK_WIDGET(file_viewer),"scrolled_window");

	//----------------------------------------------------------------------------------------------

	//------------------------------------------FINAL DEL VISOR-------------------------------------
	cont_final_visor = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	ev_final_visor = gtk_event_box_new();
	gtk_container_add(GTK_CONTAINER(cont_visor), ev_final_visor);
	gtk_widget_set_name(GTK_WIDGET(ev_final_visor), "final_visor");
	gtk_widget_set_size_request(GTK_WIDGET(ev_final_visor), 0, 20);
	label_num_archivos = gtk_label_new("Total: 67 archivos");
	gtk_container_add(GTK_CONTAINER(ev_final_visor), cont_final_visor);
	gtk_box_pack_start(GTK_BOX(cont_final_visor), label_num_archivos, 0, 0, 10);
	gtk_box_pack_start(GTK_BOX(contenedor), cont_cuerpo, 1, 1 ,10);
	//----------------------------------------------------------------------------------------------

	//Creamos la barra de estado y la anyadimos
	barra_estado = gtk_statusbar_new();
	gtk_widget_set_size_request(GTK_WIDGET(barra_estado), 0, 30);
	ev_barra_estado = gtk_event_box_new();
	gtk_widget_set_name(GTK_WIDGET(ev_barra_estado), "barra_estado");
	gtk_statusbar_push(GTK_STATUSBAR(barra_estado), 1, "Estado: Desconectado");
	gtk_container_add(GTK_CONTAINER(ev_barra_estado), barra_estado);
	gtk_container_add(GTK_CONTAINER(contenedor), ev_barra_estado);

	gtk_widget_show_all(window);

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

GtkTreeModel *create_and_fill_model ()
{
  GtkListStore *list_store;
  GdkPixbuf *p1, *p2;
  GtkTreeIter iter;
  GError *err = NULL;

  p1 = gdk_pixbuf_new_from_file ("Images/conectar.png", &err);
                            /* No error checking is done here */
  p2 = gdk_pixbuf_new_from_file ("image2.png", &err);

  list_store = gtk_list_store_new (NUM_COLS, G_TYPE_STRING, GDK_TYPE_PIXBUF);

  //Añadimos los items
  gtk_list_store_append (list_store, &iter);
  gtk_list_store_set (list_store, &iter, COL_DISPLAY_NAME, "Image1", COL_PIXBUF, p1, -1);
  gtk_list_store_append (list_store, &iter);
  gtk_list_store_set (list_store, &iter, COL_DISPLAY_NAME, "Image2", COL_PIXBUF, p2, -1);

  return GTK_TREE_MODEL (list_store);
}


void on_item_activated (GtkTreeView *view, GtkTreePath *path, GtkTreeViewColumn *col, gpointer userdata)
{
	GtkTreeIter   iter;
	GtkTreeModel *model;

	model = gtk_icon_view_get_model(GTK_ICON_VIEW(view));

	if (gtk_tree_model_get_iter(model, &iter, path))
	{
		gchar *name;

		gtk_tree_model_get(model, &iter, COL_DISPLAY_NAME, &name, -1);

		g_print ("The row containing the name '%s' has been double-clicked.\n", name);

		g_free(name);
	}
}

void on_conectar_clicked(GtkWidget *widget, gpointer c)
{
	 GtkListStore *list_store;
	  GdkPixbuf *p1, *p2;
	  GtkTreeIter iter;
	  GError *err = NULL;

	  p1 = gdk_pixbuf_new_from_file ("Images/conectar.png", &err);
								/* No error checking is done here */
	  p2 = gdk_pixbuf_new_from_file ("image2.png", &err);

	  list_store = gtk_list_store_new (NUM_COLS, G_TYPE_STRING, GDK_TYPE_PIXBUF);

	  //Añadimos los items
	  gtk_list_store_append (list_store, &iter);
	  gtk_list_store_set (list_store, &iter, COL_DISPLAY_NAME, "Pene", COL_PIXBUF, p1, -1);
	  gtk_list_store_append (list_store, &iter);
	  gtk_list_store_set (list_store, &iter, COL_DISPLAY_NAME, "Culo", COL_PIXBUF, p2, -1);

	  gtk_icon_view_set_model(GTK_ICON_VIEW(c), GTK_TREE_MODEL(list_store));
}


