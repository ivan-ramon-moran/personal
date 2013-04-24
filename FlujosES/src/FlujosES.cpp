#include <iostream>
#include <iomanip>

using namespace std;

int GetNumCaracteres(char *cadenaPtr);
int GetNumCaracteres (string cadena);

int main()
{
	char *palabra = "pene";
	char *buffer = "Hola, amigo";
	string cadena = "Hola, amigo";
	//Creamos un puntero de tipo char y lo apuntamos al primer caracter de la cadena
	//NOTA: Tenemos que hacerlo siempre asi ya que a cout.write() hay que pasarle un puntero tipo char.
	char *cadenaPtr = &cadena[0];
	//Entero que utilizado para restaurar la precision
	int precision;
	bool cBool = false;


	/*Es lo mismo que cout << buffer con la diferencia de que hay que especificar el numero
	de caracteres a mostrar*/
	cadena.push_back('\n');
	cout.write(cadenaPtr, GetNumCaracteres(cadena));


	//Coversiones con manipuladores de flujos Hex, Oct, y decimal
	//Hexadecimal
	cout << showbase  << hex << 10 << endl;
	//Octal
	cout << showbase << oct << 10 << endl;
	//Decimal
	cout << showbase << dec << 10 << endl;

	//Precision con maniluladores de flujos
	//Guardamos la precision actual
	precision = cout.precision();
	//Cambiamos la precision
	cout << setprecision(2) << 3.45677 << endl;
	//Restauramos la precision
	cout << setprecision(precision) << 3.45677 << endl;

	//Mostrar bool como true o false con manipuladores
	cout << boolalpha << cBool << endl;

	return 0;
}

//Redefinicion del metodo strlen con parametro de entrada puntero

int GetNumCaracteres (char * cadenaPtr)
{
	//Num de caracteres vamos a ir incrementando
	int num_caracteres = 0;

	//Recorremos el puntero con aritmetica de punteros hasta que encontremos terminacion de cadena.
	while (*(cadenaPtr + num_caracteres) != '\0')
	{
		//Incrementamos el numero de caracteres en 1
		num_caracteres++;
	}

	return num_caracteres;
}

//Redefinicion de strlen con parametro de entrada string

int GetNumCaracteres (string cadena)
{
	//Num de caracteres vamos a ir incrementando
	int num_caracteres = 0;

	//Recorremos el puntero con aritmetica de punteros hasta que encontremos terminacion de cadena.
	while (cadena[num_caracteres] != '\0')
	{
		//Incrementamos el numero de caracteres en 1
		num_caracteres++;
	}

	return num_caracteres;
}

