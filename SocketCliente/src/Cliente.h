#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <stdio.h> //printf
#include <string.h>    //strlen
#include <sys/socket.h>    //socket
#include <arpa/inet.h> //inet_addr
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

class Cliente
{
public:
	Cliente();

	//Setters y getters
	string GetEstado();
	void SetEstado(string estado);

	//Operaciones permitidas
	void Conectar(string direccion_ip, int puerto);
	void EnviarDatos(string mensaje);
	void RecibirDatos(vector<string> &v_resultado);
	void Sincronizar();

	//Para ordenar
	string Array2String(char cadena[], unsigned int tamanyo);
private:
	int sock;
	struct sockaddr_in server;
	char message[1000] , server_reply[2000];
	string estado;
};

#endif /* CLIENTE_H_ */
