#include "VentanaNuevoUsuario.h"

VentanaNuevoUsuario::VentanaNuevoUsuario(GtkWidget *ventana_padre)
{
	ventana = gtk_dialog_new_with_buttons(  "Nuevo usuario",
		            							GTK_WINDOW(ventana_padre),
		            							GTK_DIALOG_DESTROY_WITH_PARENT,
		            							NULL,
		            							NULL);

	Configuracion::get_instance()->ventana_nuevo_usuario = ventana;
	gtk_widget_set_size_request(GTK_WIDGET(ventana), 500, 400);
	gtk_widget_set_name(GTK_WIDGET(ventana), "ventana_nuevo_usuario");
	img_nuevo_usuario = gtk_image_new_from_file("Images/nuevo_usuario.png");
	img_importante = gtk_image_new_from_file("Images/importante.png");
	img_importante2 = gtk_image_new_from_file("Images/importante.png");
	Configuracion::get_instance()->img_usuario = img_importante;
	Configuracion::get_instance()->img_contrasenya = img_importante2;
	contenido = gtk_dialog_get_content_area(GTK_DIALOG(ventana));
	contenedor_fixed = gtk_fixed_new();
	gtk_fixed_put(GTK_FIXED(contenedor_fixed), GTK_WIDGET(img_nuevo_usuario), 0, 20);
	//-----------------------------------LABEL Y ENTRY USUARIO---------------------------------------
	//Creamos el label y el entry del nombre de usuario
	label_nombre = gtk_label_new("Nombre de usuario: ");
	entry_nombre = gtk_entry_new();
	Configuracion::get_instance()->entry_usuario_vnuevo = entry_nombre;
	gtk_fixed_put(GTK_FIXED(contenedor_fixed), GTK_WIDGET(label_nombre), 150, 30);
	gtk_fixed_put(GTK_FIXED(contenedor_fixed), GTK_WIDGET(entry_nombre), 280, 25);
	gtk_fixed_put(GTK_FIXED(contenedor_fixed), GTK_WIDGET(img_importante), 450, 25);
	gtk_widget_set_name(GTK_WIDGET(entry_nombre), "entry_nuevo_usuario_nombre");
	gtk_entry_set_alignment(GTK_ENTRY(entry_nombre), 0.5);
	g_signal_connect(G_OBJECT(entry_nombre), "changed", G_CALLBACK(ComprobarValidacion), NULL);
	//-----------------------------------------------------------------------------------------------
	//------------------------------------LABEL Y ENTRY PASSWORD-------------------------------------
	//Creamos y añadimos el label y el entry de la password
	label_pass = gtk_label_new("Contraseña: ");
	entry_pass = gtk_entry_new();
	Configuracion::get_instance()->entry_password_vnuevo = entry_pass;
	gtk_fixed_put(GTK_FIXED(contenedor_fixed), GTK_WIDGET(label_pass), 150,65);
	gtk_fixed_put(GTK_FIXED(contenedor_fixed), GTK_WIDGET(entry_pass), 280, 60);
	gtk_fixed_put(GTK_FIXED(contenedor_fixed), GTK_WIDGET(img_importante2), 450,60);
	gtk_widget_set_name(GTK_WIDGET(entry_pass), "entry_nuevo_usuario_pass");
	gtk_entry_set_alignment(GTK_ENTRY(entry_pass), 0.5);
	g_signal_connect(G_OBJECT(entry_pass), "changed", G_CALLBACK(ComprobarValidacion), NULL);

	//-----------------------------------------------------------------------------------------------
	//-----------------------------------CHECK SUPERUSUARIO------------------------------------------
	check_superusuario = gtk_check_button_new_with_label("Super usuario");
	gtk_fixed_put(GTK_FIXED(contenedor_fixed), GTK_WIDGET(check_superusuario), 150, 100);
	//-----------------------------------------------------------------------------------------------
	//------------------------------------LISTVIEW PERMISOS------------------------------------------
	lista_permisos = gtk_tree_view_new();
	scroll_lista = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(scroll_lista), lista_permisos);
	gtk_widget_set_size_request(GTK_WIDGET(scroll_lista), 460, 150);
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(lista_permisos), TRUE);
	gtk_fixed_put(GTK_FIXED(contenedor_fixed), GTK_WIDGET(scroll_lista), 20, 200);

	GtkCellRenderer *renderer_icon, *renderer_text;
	GtkTreeViewColumn *columna_ruta, *columna_permiso_e, *columna_permiso_l;
	GtkTreeStore *store;

    renderer_icon = gtk_cell_renderer_pixbuf_new();
	renderer_text = gtk_cell_renderer_text_new();
	columna_ruta = gtk_tree_view_column_new_with_attributes("Ruta", renderer_text, "text", ITEM_RUTA, NULL);
	columna_permiso_l = gtk_tree_view_column_new_with_attributes("Lectura", renderer_icon, "pixbuf", ITEM_L, NULL);
	columna_permiso_e = gtk_tree_view_column_new_with_attributes("Escritura", renderer_icon, "pixbuf", ITEM_E, NULL);

	gtk_tree_view_append_column(GTK_TREE_VIEW(lista_permisos), columna_ruta);
	gtk_tree_view_append_column(GTK_TREE_VIEW(lista_permisos), columna_permiso_l);
	gtk_tree_view_append_column(GTK_TREE_VIEW(lista_permisos), columna_permiso_e);

	gtk_tree_view_column_set_min_width(columna_ruta,260);
	gtk_tree_view_column_set_min_width(columna_permiso_l,100);
	gtk_tree_view_column_set_min_width(columna_permiso_e,100);

	store = gtk_tree_store_new(N_COLUMNS, G_TYPE_STRING, GDK_TYPE_PIXBUF, GDK_TYPE_PIXBUF);
	gtk_tree_view_set_model(GTK_TREE_VIEW(lista_permisos),GTK_TREE_MODEL(store));
	g_object_unref(store);
	//-----------------------------------------------------------------------------------------------
	//-------------------------------------COMPONENTES AÑADIR PERMISO------------------------------------
	boton_abrir_file_chooser = gtk_button_new_with_label("Abrir ");
	check_permiso_l = gtk_check_button_new_with_label("Permiso lectura");
	check_permiso_e = gtk_check_button_new_with_label("Permiso escritura");
	entry_directorio = gtk_entry_new();
	gtk_widget_set_name(GTK_WIDGET(entry_directorio), "entry_directorio");
	Configuracion::get_instance()->entry_directorio = entry_directorio;
	label_directorio = gtk_label_new("Directorio:");
	gtk_widget_set_size_request(GTK_WIDGET(entry_directorio), 340, 0);
	gtk_entry_set_alignment(GTK_ENTRY(entry_directorio), 0.5);
	Configuracion::get_instance()->check_permiso_l = check_permiso_l;
	Configuracion::get_instance()->check_permiso_e = check_permiso_e;
	boton_anyadir_permiso = gtk_button_new_with_label("Añadir");
	gtk_widget_set_size_request(GTK_WIDGET(boton_anyadir_permiso), 80, 0);
	gtk_fixed_put(GTK_FIXED(contenedor_fixed), GTK_WIDGET(check_permiso_l), 150, 135);
	gtk_fixed_put(GTK_FIXED(contenedor_fixed), GTK_WIDGET(check_permiso_e), 270, 135);
	gtk_fixed_put(GTK_FIXED(contenedor_fixed), GTK_WIDGET(boton_abrir_file_chooser), 430, 170);
	gtk_fixed_put(GTK_FIXED(contenedor_fixed), GTK_WIDGET(label_directorio), 20, 172);
	gtk_fixed_put(GTK_FIXED(contenedor_fixed), GTK_WIDGET(boton_anyadir_permiso), 400, 135);
	gtk_fixed_put(GTK_FIXED(contenedor_fixed), GTK_WIDGET(entry_directorio), 90, 168);
	g_signal_connect(G_OBJECT(boton_abrir_file_chooser), "clicked", G_CALLBACK(AbrirFileChooser), NULL);
	g_signal_connect(G_OBJECT(boton_anyadir_permiso), "clicked", G_CALLBACK(AnyadirPermiso), lista_permisos);
	//-----------------------------------------------------------------------------------------------
	//-------------------------------------BOTONES VENTANA-------------------------------------------
	contenedor_botones = gtk_dialog_get_action_area(GTK_DIALOG(ventana));
	boton_anyadir_usuario = gtk_button_new_with_label("Añadir usuario");
	g_signal_connect(G_OBJECT(boton_anyadir_usuario), "clicked", G_CALLBACK(InsertarUsuario), lista_permisos);
	gtk_widget_set_name(GTK_WIDGET(boton_anyadir_usuario), "boton_nuevo_usuario_anyadir");
	boton_cancelar = gtk_button_new_with_label("Cancelar");
	gtk_widget_set_name(GTK_WIDGET(boton_cancelar), "boton_nuevo_usuario_cancelar");
	gtk_container_add(GTK_CONTAINER(contenedor_botones), GTK_WIDGET(boton_anyadir_usuario));
	gtk_container_add(GTK_CONTAINER(contenedor_botones), GTK_WIDGET(boton_cancelar));
	//-----------------------------------------------------------------------------------------------
	gtk_container_add(GTK_CONTAINER(contenido), contenedor_fixed);
	gtk_widget_show_all(ventana);

	gtk_dialog_run(GTK_DIALOG(ventana));
}

VentanaNuevoUsuario::~VentanaNuevoUsuario() {
	// TODO Auto-generated destructor stub
}

void AbrirFileChooser()
{
	GtkWidget *file_chooser;

	//Creamos el file chooser.
	file_chooser = gtk_file_chooser_dialog_new("Directorio donde se aplicará el permiso", GTK_WINDOW(Configuracion::get_instance()->ventana_principal), GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,NULL);

	//Esperamos a que el usuario pulse el boton de aceptar y capturamos el directori que ha seleccionado
	if (gtk_dialog_run (GTK_DIALOG (file_chooser)) == GTK_RESPONSE_ACCEPT)
	{
		char *file_name;

	    file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (file_chooser));
	    Configuracion::get_instance()->directorio_seleccionado = file_name;
	    gtk_entry_set_text(GTK_ENTRY(Configuracion::get_instance()->entry_directorio), file_name);
	    g_free (file_name);
	}

	gtk_widget_destroy (file_chooser);
}

void AnyadirPermiso(GtkWidget *widget, gpointer lista)
{
	GtkTreeStore *store;
	GtkTreeIter iter;
	GdkPixbuf *icon_yes, *icon_no;
	GError *error = NULL;
	bool permiso_l = false, permiso_e = false;
	string contenido_entry_direccion;

	//Limpiamos los permisos de los vectores que utilizaremos para guardar los datos en la base de datos
	Configuracion::get_instance()->permisos_escritura.clear();
	Configuracion::get_instance()->permisos_lectura.clear();
	//Obtenemos la ruta del permiso a anyadir
	contenido_entry_direccion = gtk_entry_get_text(GTK_ENTRY(Configuracion::get_instance()->entry_directorio));

	if (contenido_entry_direccion != "")
	{
		icon_yes = gdk_pixbuf_new_from_file("Images/check.png", &error);
		icon_no = gdk_pixbuf_new_from_file("Images/delete.png", &error);

		store = GTK_TREE_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(lista)));
		gtk_tree_store_append(store, &iter, NULL);

		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Configuracion::get_instance()->check_permiso_l)))
		{
			permiso_l = true;
			Configuracion::get_instance()->permisos_lectura.push_back(contenido_entry_direccion);
		}

		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Configuracion::get_instance()->check_permiso_e)))
		{
			permiso_e = true;
			Configuracion::get_instance()->permisos_escritura.push_back(contenido_entry_direccion);
		}

		if (permiso_l && permiso_e)
			gtk_tree_store_set(store, &iter, ITEM_RUTA, (Configuracion::get_instance()->directorio_seleccionado).c_str(), ITEM_L, icon_yes, ITEM_E, icon_yes, -1);
		else
			if (!permiso_l && permiso_e)
				gtk_tree_store_set(store, &iter, ITEM_RUTA, (Configuracion::get_instance()->directorio_seleccionado).c_str(), ITEM_L, icon_no, ITEM_E, icon_yes, -1);
			else if (permiso_l && !permiso_e)
				gtk_tree_store_set(store, &iter, ITEM_RUTA, (Configuracion::get_instance()->directorio_seleccionado).c_str(), ITEM_L, icon_yes, ITEM_E, icon_no, -1);
			else
				gtk_tree_store_set(store, &iter, ITEM_RUTA, (Configuracion::get_instance()->directorio_seleccionado).c_str(), ITEM_L, icon_no, ITEM_E, icon_no, -1);
	}
	else
		Mensaje mensaje("Error de validacion", "Debes seleccionar un directorio donde aplicar los permisos.", Configuracion::get_instance()->ventana_principal);
}

void ComprobarValidacion(GtkWidget *entry)
{
	string contenido_entry;
	string nombre_widget;

	nombre_widget = gtk_widget_get_name(GTK_WIDGET(entry));
	contenido_entry = gtk_entry_get_text(GTK_ENTRY(entry));

	if (contenido_entry.length() >= 3 && contenido_entry.length() <= 10)
		if (nombre_widget == "entry_nuevo_usuario_nombre")
			gtk_image_set_from_file(GTK_IMAGE(Configuracion::get_instance()->img_usuario), "Images/verificado.png");
		else
			gtk_image_set_from_file(GTK_IMAGE(Configuracion::get_instance()->img_contrasenya), "Images/verificado.png");
	else
		if (nombre_widget == "entry_nuevo_usuario_nombre")
			gtk_image_set_from_file(GTK_IMAGE(Configuracion::get_instance()->img_usuario), "Images/importante.png");
		else
			gtk_image_set_from_file(GTK_IMAGE(Configuracion::get_instance()->img_contrasenya), "Images/importante.png");
}

void InsertarUsuario(GtkWidget *widget, GtkTreeView *lista_permisos)
{
	string usuario, password, sentencia;
	bool existe;
	int id_usuario;

	//Obtenemos de configuracion los valores que el usuario ha introducido en los campos
	usuario = gtk_entry_get_text(GTK_ENTRY(Configuracion::get_instance()->entry_usuario_vnuevo));
	password = gtk_entry_get_text(GTK_ENTRY(Configuracion::get_instance()->entry_password_vnuevo));
	//Comprobamos si el usuario existe en la BD
	sentencia = "SELECT * FROM usuarios WHERE usuario LIKE '" + usuario + "'";
	existe = BD::ComprobarConsulta("NetTransfer.db", sentencia);

	//Si no existe lo agregamos y si existe mostramos un mensaje de error al usuario.
	if (!existe)
	{
		sentencia = "INSERT INTO usuarios (usuario, password) VALUES ('" + usuario + "'" + ",'" + password + "')";
		BD::EjecutarOperacion("NetTransfer.db", sentencia);
		//------------------------------------------PERMISOS--------------------------------------------------------------------
		//Obenemos el id del usuario que acabamos de insertar
		sentencia = "SELECT id FROM usuarios WHERE usuario LIKE '" + usuario + "'";
		id_usuario = BD::ConsultaInt("NetTransfer.db", sentencia);
		//----------------------------------------------------------------------------------------------------------------------
	}
	else
		Mensaje mensaje("Error usuario ya existente", "El usuario ya existe en la base da datos", Configuracion::get_instance()->ventana_principal);

	gtk_widget_destroy(GTK_WIDGET(Configuracion::get_instance()->ventana_nuevo_usuario));
}

