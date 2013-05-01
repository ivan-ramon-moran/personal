#ifndef SERVER_H_
#define SERVER_H_

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
#include "Config.h"

using namespace std;

class Server
{
public:
	Server();
	Server(int port);
	void Escuchar();
	void EnviarDatos(char []);
	void EnviarDatos(int numero);
	void EnviarDatos(vector<string> &vector);
	void EnviarArchivo(string path);
	bool GetReady();
	string Array2String(char cadena[], unsigned int tamanyo);
	void Close();
	string GetEstadoCliente();
	string RecibirDatos();
	void RecibirFichero();
	void SendReady();
	void SetConf(Config &config);

private:
	int socket_desc, client_sock , c , read_size;
	struct sockaddr_in server , client;
	char client_message[2000];
	string estado_cliente;
	string ObtenerNombreFichero(string path);
	Config config;
};

#endif /* SERVER_H_ */
