#include <string.h>    //strlen
#include <sys/socket.h>    //socket
#include <sys/stat.h>
#include <arpa/inet.h> //inet_addr
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <exception>
#include "ExcepcionPersonalizada.h"
#include "Archivo.h"
#include "Directorio.h"
#include "UtilidadesTipos.h"

using namespace std;

#ifndef CLIENTE_H_
#define CLIENTE_H_

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
	void SendReady();
	void RecibirFichero();
	void EnviarArchivo(string path);
	string ObtenerNombreFichero(string path);
	bool GetReady();
	void Cerrar();
	void DeserializarObjeto(vector<Archivo> &v_archivos);

	//Para meter en una clase utilidades con metodo estatico
	string Array2String(char cadena[], unsigned int tamanyo);
private:
	int sock;
	struct sockaddr_in server;
	char message[1000] , server_reply[2000];
	string estado;
};

#endif /* CLIENTE_H_ */
