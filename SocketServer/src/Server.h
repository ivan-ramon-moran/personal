#ifndef SERVER_H_
#define SERVER_H_

#include <iostream>
#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>
#include <sstream>
#include <vector>

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
	bool Sincronizar();
	string Array2String(char cadena[], unsigned int tamanyo);
	void Close();
	string GetEstadoCliente();
	string RecibirDatos();

private:
	int socket_desc, client_sock , c , read_size;
	struct sockaddr_in server , client;
	char client_message[2000];
	string estado_cliente;
};

#endif /* SERVER_H_ */
