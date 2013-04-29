#include <iostream>
#include "Server.h"
#include "Directorio.h"

using namespace std;

int main()
{
	Server server(8888);
	vector<string> v_resultados;

	string mensaje;

	while (1)
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

	return 0;
}


