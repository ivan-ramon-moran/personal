#include <iostream>
#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>
#include <sstream>
#include <vector>
#include <fstream>
#include <pthread.h>
#include <gtk/gtk.h>
#include "Archivo.h"
#include "Directorio.h"
#include "UtilidadesTipos.h"

using namespace std;

#ifndef SERVER_H_
#define SERVER_H_

class Server
{
public:
	Server();
	Server(int port);
	void Escuchar();
	void EnviarDatos(int numero);
	void EnviarDatos(string mensaje);
	void EnviarDatos(vector<string> &vector);
	void EnviarArchivo(string path);
	bool GetReady();
	string Array2String(char cadena[], unsigned int tamanyo);
	void Close();
	string GetEstadoCliente();
	string RecibirDatos();
	void RecibirFichero();
	void SendReady();
	string GetEstado();
	void SetLabelEstado(GtkWidget *label);
	void SerializarObjeto(vector<Archivo> &vector);
	void DesconectarCliente();

private:
	int socket_desc, client_sock , c , read_size;
	struct sockaddr_in server , client;
	char client_message[2000];
	string estado_servidor, estado_cliente;
	string ObtenerNombreFichero(string path);
	//Config config;
	GtkWidget *label_estado;
};

#endif /* SERVER_H_ */
