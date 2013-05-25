#ifndef CONF_H__
#define CONF_H__

#include <iostream>
#include "FileViewer.h"
#include "Cliente.h"
#include "Server.h"

using namespace std;

class Configuracion
{
public:
	Configuracion();

	//Metodo para devolver la instancia de la clase
	static Configuracion* get_instance();

	//Atributos
	FileViewer *file_viewer;
	Server *server;
	Cliente *cliente;
	GtkWidget *ventana_principal;
	//Puntero hacia la ventana de autentificacion de usuarios para poder cerrarla ya que la señal obliga a que sea un metodo estatico
	GtkWidget *ventana_aut;
	//entry direccion y entry puerto. Punteros hacia los campos de conexion de la ventana principal
	GtkWidget *entry_direccion;
	GtkWidget *entry_puerto;
	//Puntero hacia el boton de conectar para poder cambiar la imagen
	GtkWidget *boton_conectar;
	//Estado del cliente para controlar si conectar o desconectar en el boton de la ventana principal
	int estado;
	//Punteros hacia los campos de usuario y contraseña
	GtkWidget *entry_usuario;
	GtkWidget *entry_password;
	//string a campos de usuario y contraseña de la ventana de autentificacion
	string usuario;
	string password;
	bool mostrar_archivos_ocultos;
	vector<Archivo> elementos;
	/*Punteros que hacen referencia a los componentes gráficos del visor de achivos para mostrar
	  los atributos de cada archivo/directorio*/
	GtkWidget *label_nombre, *label_ruta, *label_tipo, *label_tamanyo;

private:
	static Configuracion *instance;
};

#endif
