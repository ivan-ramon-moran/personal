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
			if (GetReady())
			{
				if (write(client_sock, vector[i].c_str(), strlen(vector[i].c_str())) < 0)
					cout << "Error en la transferencia" << endl;
			}

		}

		//El servidor espera un ok todavia del ultimo elemento.
		GetReady();
	}
	else
		cout << "Error en la transferencia" << endl;
}

bool Server::GetReady()
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

void Server::SendReady()
{
	char ok[] = "ok";

	if (write(client_sock, ok, strlen(ok)) < 0)
		cout << "Error en la sincronización" << endl;
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

void Server::EnviarArchivo(string path)
{
	char *data = new char[1024];
	ifstream file;
	struct stat filestatus;
	unsigned long long tamanyo_fichero;
	string nombre_fichero;

	//tamanyo del fichero
	stat(path.c_str() , &filestatus );
	tamanyo_fichero = filestatus.st_size;

	//Abrimos el fichero
	file.open(path.c_str(), ios::binary);

	//Si hemos podido abrir el fichero, empezamos a leerlo y mandarlo
	if (file)
	{
		//Enviamos el nombre del fichero.
		nombre_fichero = ObtenerNombreFichero(path);
		write(client_sock, nombre_fichero.c_str(), sizeof(nombre_fichero.c_str()));
		GetReady();
		//Leemos el archivo y lo enviamos.
		while (file.read(data, 1024))
		{
			write(client_sock, data, 1024);
			tamanyo_fichero -= 1024;
		}

		write(client_sock, data, tamanyo_fichero);


		file.close();
	}

}

void Server::RecibirFichero()
{
	ofstream file;
	char *data = new char[1024];
	char c_nombre_fichero[100];
	int num_bytes;
	string nombre_fichero, ruta_entrada, ruta_completa;

	//Recibimos el nombre del fichero
	num_bytes = recv(client_sock, c_nombre_fichero, 100, 0);
	SendReady();
	nombre_fichero = Array2String(c_nombre_fichero, num_bytes);

	//Creamos la ruta completa donde guardaremos el fichero
	ruta_entrada = "/home/k3rnel/Escritorio/transferencias/";
	ruta_completa = ruta_entrada + nombre_fichero;

	file.open(ruta_completa.c_str(), ios::binary);

	if (file)
	{
		//Recibimos el archivo
		while ((num_bytes = recv(client_sock, data, 1024,0)) > 0)
			file.write(data, num_bytes);

		//El ultimo bloque de datos que falta por que no puede leer 1024 bytes y por lo tanto no entra al while.
		num_bytes = recv(client_sock, data, 1024,0);
		file.write(data, num_bytes);

		file.close();
	}
}

string Server::ObtenerNombreFichero(string path)
{
	string nombre;
	int posicion;

	//Recorremos la cadena y nos quedamos con la ultima aparicion de '/'
	for (unsigned int i = 0; i < path.length(); i++)
		if (path[i] == '/')
			posicion = i;

	//Asignamos a nombre la subcadena desde la aparicion de '/' hasta el final
	nombre = path.substr(posicion + 1, path.length());

	return nombre;
}
