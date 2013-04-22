/* Autor Iván Rámon Morán @ K3rneL
 * Punteros
 * Propisito: Utilizamiento basico de los punteros
 * Conclusion: Cuando los punteros son datos simple (int, char, float, double) y strings la variable en si
 * hace referencia a la direccion de memoria y para hacer referencia al contenido del puntero
 * se utiliza *, ejem: *numeroPtr = 1 (Para asignar y obtener);
 * Por el contrario cuando son Arrays y cualquier tipo de objeto (EXCEPTUANDO STRINGS) se utiliza para hacer referencia
 * al contenido el nombre del puntero sin *.
 */

#include <iostream>

using namespace std;

int main()
{
	char *cadenaPtr = "Hola maria";
	string cadena = "Hola pepe";
	string *stringPtr = &cadena;
	string cadena2 = "jsjsjss";
	string *cadena2Ptr = new string;
	int *mi_vector = new int[5];
	mi_vector[0] = 3;

	//Cuando se pone el puntero no referimos siempre al contenido
	//Mientras el contenido no sea final de cadena
	while (*cadenaPtr != NULL)
	{
		//Mostramos el contenido
		cout << *cadenaPtr;
		//Incrementamos uno a la posicion de memoria
		cadenaPtr++;
	}

	stringPtr = &cadena;
	*cadena2Ptr = "pene";

	stringPtr = cadena2Ptr;

	cout << *stringPtr << endl;
	cout << mi_vector[0] << endl;
	return 0;
}
