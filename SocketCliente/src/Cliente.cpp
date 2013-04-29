#include "Cliente.h"

Cliente::Cliente()
{
	SetEstado("Desconectado");
}

//Setters y Getters
string Cliente::GetEstado()
{
	return this->estado;
}

void Cliente::SetEstado(string estado)
{
	this->estado = estado;
}

void Cliente::Conectar(string direccion_ip, int puerto)
{
	 //Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");

	server.sin_addr.s_addr = inet_addr(direccion_ip.c_str());
	server.sin_family = AF_INET;
	server.sin_port = htons(puerto);

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) == 0)
	{
		cout << "Connected\n" << endl;
		SetEstado("conectado");
	}
	else
		perror("connect failed. Error");
}

void Cliente::EnviarDatos(string mensaje)
{
	if (send(sock, mensaje.c_str(), strlen(mensaje.c_str()), 0) > 0)
		cout << "Mensaje enviado" << endl;
}

void Cliente::RecibirDatos(vector<string> &v_resultado)
{
	char c_tamanyo[10], c_elemento[100];
	unsigned int num_elementos = 0;
	int num_bytes;
	string elemento;

	//Recibimos el tamanyo del vector que nos van a enviar para saber cuantas veces iterar
	if (recv(sock, c_tamanyo, 10, 0) > 0)
	{
		num_elementos = atoi(c_tamanyo);
		cout << "Num elementos: " << num_elementos << endl;

		//Sincronizamos los sockets
		Sincronizar();

		//Recibimos los elementos
		for (unsigned int i = 0; i < num_elementos; i++)
		{
			num_bytes = recv(sock, c_elemento, 100, 0);

			if (num_bytes != 0)
			{
				elemento = Array2String(c_elemento, num_bytes);
				v_resultado.push_back(elemento);
				//Sincronizamos los sockets
				Sincronizar();
			}
			//OJO!!! tenemos que borrar el array en cada iteracion.
			bzero(c_elemento, strlen(c_elemento));
		}

	}

}

void Cliente::Sincronizar()
{
	char ok[] = "ok";

	if (send(sock, ok, strlen(ok), 0) < 0)
		cout << "Error en la sincronización" << endl;

}

string Cliente::Array2String(char cadena[], unsigned int tamanyo)
{
	string resultado;

	for (unsigned int i = 0; i < tamanyo; i++)
	{
		resultado += cadena[i];
	}

	return resultado;
}
