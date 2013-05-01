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

using namespace std;

class Server
{
public:
	Server();
	Server(int port);
	void Escuchar();
	void Pene();
	void Pene2();
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

private:
	int socket_desc, client_sock , c , read_size;
	struct sockaddr_in server , client;
	char client_message[2000];
	string estado_cliente;
	string ObtenerNombreFichero(string path);
};

#endif /* SERVER_H_ */
