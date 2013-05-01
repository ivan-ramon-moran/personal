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
		GetReady();

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
		SendReady();

		//Recibimos los elementos
		for (unsigned int i = 0; i < num_elementos; i++)
		{
			num_bytes = recv(sock, c_elemento, 100, 0);

			if (num_bytes != 0)
			{
				elemento = Array2String(c_elemento, num_bytes);
				v_resultado.push_back(elemento);
				//Sincronizamos los sockets
				SendReady();
			}
			//OJO!!! tenemos que borrar el array en cada iteracion.
			bzero(c_elemento, strlen(c_elemento));
		}

	}

}

void Cliente::RecibirFichero()
{
	ofstream file;
	char *data = new char[1024];
	char c_nombre_fichero[100];
	int num_bytes;
	string nombre_fichero, ruta_entrada, ruta_completa;

	//Recibimos el nombre del fichero
	num_bytes = recv(sock, c_nombre_fichero, 100, 0);
	nombre_fichero = Array2String(c_nombre_fichero, num_bytes);

	//Creamos la ruta completa donde guardaremos el fichero
	ruta_entrada = "/home/k3rnel/Escritorio/transferencias/";
	ruta_completa = ruta_entrada + nombre_fichero;

	file.open(ruta_completa.c_str(), ios::binary);

	if (file)
	{

		num_bytes = recv(sock, data, 1024,0);

		//Recibimos el archivo
		while (num_bytes == 1024)
		{
			cout << num_bytes << endl;
			file.write(data, num_bytes);
			num_bytes = recv(sock, data, 1024,0);
		}

		file.write(data, num_bytes);

		cout << "Recibido" << endl;

		file.close();
	}
}

void Cliente::EnviarArchivo(string path)
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
	if (file )
	{
		cout << "Ready!!!" << endl;
		//Enviamos el nombre del fichero.
		nombre_fichero = ObtenerNombreFichero(path);
		send(sock, nombre_fichero.c_str(), sizeof(nombre_fichero.c_str()), 0);
		GetReady();
		//Leemos el archivo y lo enviamos.
		while (file.read(data, 1024))
		{
			send(sock, data, 1024, 0);
			tamanyo_fichero -= 1024;
		}

		send(sock, data, tamanyo_fichero, 0);


		file.close();
	}

}

void Cliente::SendReady()
{
	char ok[] = "ok";

	if (send(sock, ok, strlen(ok), 0) < 0)
		cout << "Error en la sincronización" << endl;

}

bool Cliente::GetReady()
{
	bool esta_correcta = false;
	char *cadena_recibida = new char[2];
	char *cadena_correcta = "ok";

	if (recv(sock, cadena_recibida, 2, 0) > 0)
	{
		if (*cadena_recibida == *cadena_correcta)
			esta_correcta = true;
	}

	return esta_correcta;
}

string Cliente::ObtenerNombreFichero(string path)
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

string Cliente::Array2String(char cadena[], unsigned int tamanyo)
{
	string resultado;

	for (unsigned int i = 0; i < tamanyo; i++)
	{
		resultado += cadena[i];
	}

	return resultado;
}
