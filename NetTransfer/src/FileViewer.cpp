#include "FileViewer.h"

FileViewer::FileViewer(){}

FileViewer::FileViewer(GtkWidget *contenedor_padre)
{
	//Deberiamos de vaciar la pila
	rutas.Apilar("/");

	this->contenedor_padre = contenedor_padre;
	g = NULL;

	//Creamos el area de scroll
	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolled_window), GTK_SHADOW_IN);

	//Visor de archivos
	file_viewer = gtk_icon_view_new();
	gtk_icon_view_set_text_column (GTK_ICON_VIEW (file_viewer), COL_DISPLAY_NAME);
	gtk_icon_view_set_pixbuf_column (GTK_ICON_VIEW (file_viewer), COL_PIXBUF);
	gtk_icon_view_set_selection_mode (GTK_ICON_VIEW (file_viewer), GTK_SELECTION_MULTIPLE);

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

	gtk_box_pack_start(GTK_BOX(contenedor_padre),cont_visor, 1, 1, 10);
	gtk_container_add (GTK_CONTAINER (scrolled_window), file_viewer);
	gtk_widget_set_name(GTK_WIDGET(file_viewer),"scrolled_window");

	//------------------------------------------FINAL DEL VISOR-------------------------------------
	cont_final_visor = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	ev_final_visor = gtk_event_box_new();
	gtk_container_add(GTK_CONTAINER(cont_visor), ev_final_visor);
	gtk_widget_set_name(GTK_WIDGET(ev_final_visor), "final_visor");
	gtk_widget_set_size_request(GTK_WIDGET(ev_final_visor), 0, 20);
	label_num_archivos = gtk_label_new("");
	gtk_container_add(GTK_CONTAINER(ev_final_visor), cont_final_visor);
	gtk_box_pack_start(GTK_BOX(cont_final_visor), label_num_archivos, 0, 0, 10);
	//----------------------------------------------------------------------------------------------

	//Señales
	g_signal_connect(G_OBJECT(file_viewer), "item-activated", G_CALLBACK(on_item_activated), NULL);
	//g_signal_connect(G_OBJECT(file_viewer), "selection-changed", G_CALLBACK(on_item_one_click), NULL);

}

GtkTreeModel* FileViewer::create_and_fill_model ()
{
	GtkListStore *list_store;
	GdkPixbuf *img_folder, *img_text, *img_zip, *img_pdf, *img_png, *img_mp3, *img_jpg, *img_app;
	GdkPixbuf *img_rar, *img_word, *img_odt, *img_gz;
	GtkTreeIter iter;
	GError *err = NULL;
	stringstream s;
	int tipo = 0;

	list_store = gtk_list_store_new (NUM_COLS, G_TYPE_STRING, GDK_TYPE_PIXBUF);

	for (unsigned int i = 0; i < elementos.size(); i++)
	{
		tipo = ObtenerTipo(elementos.at(i).get_tipo());
		gtk_list_store_append (list_store, &iter);

		//Añadimos los items
		switch (tipo)
		{
		  case 0:
			  img_folder = gdk_pixbuf_new_from_file ("Images/folder.png", &err);
			  gtk_list_store_set (list_store, &iter, COL_DISPLAY_NAME, elementos.at(i).get_nombre().c_str(), COL_PIXBUF, img_folder, -1);
			  break;
		  case 1:
			  img_text = gdk_pixbuf_new_from_file ("Images/text-plain.png", &err);
			  gtk_list_store_set (list_store, &iter, COL_DISPLAY_NAME, elementos.at(i).get_nombre().c_str(), COL_PIXBUF, img_text, -1);
			  break;
		  case 2:
			  img_pdf = gdk_pixbuf_new_from_file("Images/application-pdf.png", &err);
			  gtk_list_store_set (list_store, &iter, COL_DISPLAY_NAME, elementos.at(i).get_nombre().c_str(), COL_PIXBUF, img_pdf, -1);
			  break;
		  case 3:
			  img_png = gdk_pixbuf_new_from_file("Images/image-png.png", &err);
			  gtk_list_store_set (list_store, &iter, COL_DISPLAY_NAME, elementos.at(i).get_nombre().c_str(), COL_PIXBUF, img_png, -1);
			  break;
		  case 4:
			  img_zip = gdk_pixbuf_new_from_file ("Images/application-x-zip.png", &err);
			  gtk_list_store_set (list_store, &iter, COL_DISPLAY_NAME, elementos.at(i).get_nombre().c_str(), COL_PIXBUF, img_zip, -1);
			  break;
		  case 5:
			  img_mp3 = gdk_pixbuf_new_from_file("Images/audio-x-mpeg.png", &err);
			  gtk_list_store_set (list_store, &iter, COL_DISPLAY_NAME, elementos.at(i).get_nombre().c_str(), COL_PIXBUF, img_mp3, -1);
			  break;
		  case 6:
			  img_jpg = gdk_pixbuf_new_from_file("Images/image-jpeg.png", &err);
			  gtk_list_store_set (list_store, &iter, COL_DISPLAY_NAME, elementos.at(i).get_nombre().c_str(), COL_PIXBUF, img_jpg, -1);
			  break;
		  case 7:
			  img_app = gdk_pixbuf_new_from_file("Images/application-x-executable.png", &err);
			  gtk_list_store_set (list_store, &iter, COL_DISPLAY_NAME, elementos.at(i).get_nombre().c_str(), COL_PIXBUF, img_app, -1);
			  break;
		  case 8:
			  img_rar = gdk_pixbuf_new_from_file("Images/application-x-rar.png", &err);
			  gtk_list_store_set (list_store, &iter, COL_DISPLAY_NAME, elementos.at(i).get_nombre().c_str(), COL_PIXBUF, img_rar, -1);
			  break;
		  case 9:
			  img_word = gdk_pixbuf_new_from_file("Images/application-msword.png", &err);
			  gtk_list_store_set (list_store, &iter, COL_DISPLAY_NAME, elementos.at(i).get_nombre().c_str(), COL_PIXBUF, img_word, -1);
			  break;
		  case 10:
			  img_odt = gdk_pixbuf_new_from_file("Images/x-office-document.png", &err);
			  gtk_list_store_set (list_store, &iter, COL_DISPLAY_NAME, elementos.at(i).get_nombre().c_str(), COL_PIXBUF, img_odt, -1);
			  break;
		  case 11:
			  img_gz = gdk_pixbuf_new_from_file("Images/application-x-gzip.png", &err);
			  gtk_list_store_set (list_store, &iter, COL_DISPLAY_NAME, elementos.at(i).get_nombre().c_str(), COL_PIXBUF, img_gz, -1);
			  break;
		}
	}

	gtk_label_set_text(GTK_LABEL(label_num_archivos), ("Total: " + s.str() + " Archivos").c_str());

    return GTK_TREE_MODEL (list_store);
}

void FileViewer::on_item_activated (GtkTreeView *view, gpointer userdata)
{
	vector<Archivo> v_resultados;
	string ruta, ultima_ruta;
	GtkTreeIter iter;
	GtkTreeModel *model;
	GList *lista;

	model = gtk_icon_view_get_model(GTK_ICON_VIEW(view));
	lista = gtk_icon_view_get_selected_items(GTK_ICON_VIEW(view));

	if (Configuracion::get_instance()->cliente->GetEstado() == "conectado")
	{
		if (gtk_tree_model_get_iter(model, &iter, (GtkTreePath *)lista->data))
		{
			gchar *item;
			//Obtenemos el item seleccionado
			gtk_tree_model_get(model, &iter, COL_DISPLAY_NAME, &item, -1);
			rutas.ObtenerValor(ultima_ruta);
			rutas.Apilar(ultima_ruta + item + "/");
			//Tenemos que comprobar si el cliente esta conectado
			//Obtenemos la ruta correspoendiente
			rutas.ObtenerValor(ruta);
			Configuracion::get_instance()->cliente->EnviarDatos(ruta);
			//Recibimos los resultados
			Configuracion::get_instance()->cliente->DeserializarObjeto(v_resultados);
			cout << v_resultados[0].get_nombre() << endl;
			//Los seteamos en el file_viewer
			Configuracion::get_instance()->file_viewer->set_items(v_resultados);
			g_free(item);
		}
	}
	else
		cout << "No estas conectado a ningun servidor." << endl;
}

void FileViewer::on_item_one_click(GtkWidget *icon_view, gpointer userdata)
{
	GtkTreeIter iter;
	GtkTreeModel *model;
	GList *lista;
	int posicion_item;

	model = gtk_icon_view_get_model(GTK_ICON_VIEW(icon_view));
	lista = gtk_icon_view_get_selected_items(GTK_ICON_VIEW(icon_view));

	if (gtk_tree_model_get_iter(model, &iter, (GtkTreePath *)lista->data))
	{
		gchar *item;
		//Obtenemos el item seleccionado
		gtk_tree_model_get(model, &iter, COL_DISPLAY_NAME, &item, -1);
		//Buscamos el item en el vector de archivos
		posicion_item = buscar_item(item);
		item_seleccionado = item;
		//Extraemos el archivo y seteamos los valores en el visor de archivos
		Archivo arch = Configuracion::get_instance()->elementos.at(posicion_item);
		gtk_label_set_text(GTK_LABEL(Configuracion::get_instance()->label_nombre), arch.get_nombre().c_str());
		gtk_label_set_text(GTK_LABEL(Configuracion::get_instance()->label_ruta), arch.get_ruta().c_str());
		gtk_label_set_text(GTK_LABEL(Configuracion::get_instance()->label_tipo), arch.get_tipo().c_str());
		gtk_label_set_text(GTK_LABEL(Configuracion::get_instance()->label_tamanyo), (UtilidadesTipos::LongToString(arch.get_tamanyo()) + " Bytes").c_str());
		g_free(item);
	}
}

void FileViewer::set_items(vector<Archivo> &vector_archivos)
{
	this->elementos = vector_archivos;
	Configuracion::get_instance()->elementos = vector_archivos;
	gtk_icon_view_set_model(GTK_ICON_VIEW(file_viewer), create_and_fill_model());
}

int FileViewer::ObtenerTipo(string tipo)
{
	int resultado = 0;

	if (tipo == "inode/directory")
		resultado = 0;
	else
		if (tipo == "text/plain")
			resultado = 1;
		else
			if (tipo == "application/pdf")
				resultado = 2;
			else
				if (tipo == "image/png")
					resultado = 3;
				else
					if (tipo == "application/zip")
						resultado = 4;
					else
						if (tipo == "audio/mpeg")
							resultado = 5;
						else
							if (tipo == "image/jpeg")
								resultado = 6;
							else
								if (tipo == "application/octet-stream")
									resultado = 7;
								else
									if (tipo == "application/x-rar")
										resultado = 8;
									else
										if (tipo == "application/msword")
											resultado = 9;
										else
											if (tipo == "application/vnd.oasis.opendocument.text")
												resultado = 10;
											else
												if (tipo == "application/x-compressed-tar")
													resultado = 11;

	return resultado;
}

int FileViewer::buscar_item(string item)
{
	int posicion = 0;

	for (unsigned int i = 0; i < Configuracion::get_instance()->elementos.size(); i++)
	{
		Archivo arch = Configuracion::get_instance()->elementos.at(i);

		if (arch.get_nombre() == item)
			posicion = i;
	}

	return posicion;
}

void FileViewer::eliminar_elementos()
{
	GtkListStore *store;
	GtkTreeModel *model;
	GtkTreeIter  iter;

	store = GTK_LIST_STORE(gtk_icon_view_get_model(GTK_ICON_VIEW (file_viewer)));
	model = gtk_icon_view_get_model (GTK_ICON_VIEW (file_viewer));

	if (gtk_tree_model_get_iter_first(model, &iter) == FALSE)
		return;

	gtk_list_store_clear(store);
	rutas.Vaciar();
	rutas.Apilar("/");
}
