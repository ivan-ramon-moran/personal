#include <iostream>
#include "Cliente.h"

using namespace std;

int main()
{
	Cliente cliente;
	vector<string> v_resultados;
	string mensaje;

	cliente.Conectar("127.0.0.1", 8888);
	cin >> mensaje;

	while (mensaje != "salir")
	{

		cliente.EnviarDatos(mensaje);

		cliente.RecibirDatos(v_resultados);

		for (unsigned int i = 0; i < v_resultados.size(); i++)
		{
			cout << v_resultados[i] << endl;
		}

		v_resultados.clear();
		cout << v_resultados.size() << endl;
		cin >> mensaje;
	}

	//Enviamos el mensaje de salida
	cliente.EnviarDatos("salir");
}
