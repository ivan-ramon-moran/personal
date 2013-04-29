#include "Server.h"


Server::Server() {}

Server::Server(int puerto)
{
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);

	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}

	puts("Socket created");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( puerto );

	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print the error message
	    perror("bind failed. Error");
	}

	puts("bind done");
}

void Server::Escuchar()
{
	//Listen
	listen(socket_desc , 3);

	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);

	//accept connection from an incoming client
	client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);

	if (client_sock < 0)
	{
		perror("accept failed");
	}
	puts("Connection accepted");
	this->estado_cliente = "conectado";
}

string Server::RecibirDatos()
{
	string resultado;

	bzero(client_message, 2000);
	read_size = recv(client_sock , client_message , 2000 , 0);

	if(read_size == 0)
	{
		puts("Client disconnected");
		this->estado_cliente = "desconectado";
		resultado = "salir";
		fflush(stdout);
	}
	else if(read_size == -1)
	{
		perror("recv failed");
	}
	else
		resultado = Array2String(client_message, read_size);


	return resultado;
}

void Server::EnviarDatos(char cadena[])
{
	if (write(client_sock, cadena, strlen(cadena)) < 0)
	    cout << "Error en la transferencia";
}

void Server::EnviarDatos(vector<string> &vector)
{
	stringstream ss;
	string str_tamanyo;

	/*Convertimos el numero de posiciones que tiene el vector que pasamos como parametro de entrada
	  a string para poder enviarlo al cliente.*/
	ss << vector.size();
	str_tamanyo = ss.str();

	//Enviamos el tamanyo y si podemos enviar el tamanyo enviamos el vector.
	if (write(client_sock, str_tamanyo.c_str(), strlen(str_tamanyo.c_str())) > 0)
	{
		for (unsigned int i = 0; i < vector.size(); i++)
		{
			if (Sincronizar())
			{
				if (write(client_sock, vector[i].c_str(), strlen(vector[i].c_str())) < 0)
					cout << "Error en la transferencia" << endl;
			}

		}

		//El servidor espera un ok todavia del ultimo elemento.
		Sincronizar();
	}
	else
		cout << "Error en la transferencia" << endl;
}

bool Server::Sincronizar()
{
	bool esta_correcta = false;
	char *cadena_recibida = new char[2];
	char *cadena_correcta = "ok";

	if (recv(client_sock, cadena_recibida, 2, 0) > 0)
	{
		if (*cadena_recibida == *cadena_correcta)
			esta_correcta = true;
	}

	return esta_correcta;
}

string Server::Array2String(char cadena[], unsigned int tamanyo)
{
	string resultado;

	for (unsigned int i = 0; i < tamanyo; i++)
	{
		resultado += cadena[i];
	}

	return resultado;
}

string Server::GetEstadoCliente()
{
	return this->estado_cliente;
}

void Server::Close()
{

}
