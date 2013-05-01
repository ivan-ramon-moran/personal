#include <iostream>
#include "Server.h"
#include "Directorio.h"

using namespace std;

int main()
{
	Server server(8888);
	vector<string> v_resultados;
	Config config;
	string mensaje;
	ifstream f_ent;
	string ruta_entrada;
	int t_buffer;

	f_ent.open("config.cfg");

	if (f_ent)
	{
		f_ent >> ruta_entrada;
		f_ent >> t_buffer;

		//Cerramos el fichero
		f_ent.close();
		config.SetRutaEntrada(ruta_entrada);
		config.SetTamBuffer(t_buffer);
	}
	else
		cout << "No se ha podido leer el archivo de configuracion" << endl;

	server.SetConf(config);


	/*while (1)
	{
		server.Escuchar();

		mensaje = server.RecibirDatos();

		cout << mensaje << endl;

		while (mensaje != "salir" || server.GetEstadoCliente() != "desconectado")
		{
			cout << "El mensaje es: " << mensaje << endl;
			Directorio::ListarDirectorio(mensaje, v_resultados);
			server.EnviarDatos(v_resultados);
			v_resultados.clear();
			mensaje.clear();
			mensaje = server.RecibirDatos();
		}
	}
	*/

	while (1)
	{
		server.Escuchar();
		mensaje = server.RecibirDatos();

		while (mensaje != "salir" || server.GetEstadoCliente() != "desconectado")
		{
			cout << mensaje << endl;
			server.EnviarArchivo(mensaje);
			mensaje.clear();
			mensaje = server.RecibirDatos();
		}
	}



	return 0;
}


