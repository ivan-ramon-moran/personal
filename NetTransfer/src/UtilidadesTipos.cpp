#include "UtilidadesTipos.h"

UtilidadesTipos::UtilidadesTipos() {}

string UtilidadesTipos::ArrayToString(char *array)
{
	string cadena = "";

	for (unsigned int i = 0; i < strlen(array); i++)
	{
		cadena += array[i];
	}

	return cadena;
}

string UtilidadesTipos::ArrayToString(char array[], int tamanyo)
{
	string cadena = "";

	for (int i = 0; i < tamanyo; i++)
	{
		cadena += array[i];
	}

	return cadena;
}

int UtilidadesTipos::ArrayToInt(char array[], int tamanyo)
{
	int resultado = 0;
	string str_array = ArrayToString(array, tamanyo);
	int numero;

	for (int i = 0; i < tamanyo; i++)
	{
		numero = str_array[i] - '0';
		resultado = resultado * 10 + numero;
	}

	return resultado;
}

unsigned long long UtilidadesTipos::ArrayToLong(char array[], int tamanyo)
{
	unsigned long long resultado = 0;
	int numero;

	for (int i = 0; i < tamanyo; i++)
	{
		numero = array[i] - '0';
		resultado = resultado * 10 + numero;
	}

	return resultado;
}


string UtilidadesTipos::IntToString(int numero)
{
	string resultado;
	int num_aux = numero;
	int num_digitos = 1;
	int ultimo_digito;
	int factor = 1;

	while (num_aux > 9)
	{
		num_aux = num_aux % 10;
		num_digitos++;
	}

	while (numero > 9)
	{
		factor = 1;

		//Calculamos el factor
		for (int i = num_digitos - 1; i > 0; i--)
			factor *= 10;

		ultimo_digito = numero / factor;
		numero = numero % factor;

		resultado += ultimo_digito + '0';
	}

	resultado += numero + '0';

	return resultado;
}

void UtilidadesTipos::StringToArray(string cadena, char array[])
{
	for (unsigned int i = 0; i < cadena.length(); i++)
	{
		array[i] = cadena[i];
	}
}

void UtilidadesTipos::LongToArray(unsigned long long numero, char array[])
{
	string resultado;
	unsigned long long num_aux = numero;
	int num_digitos = 1;
	int ultimo_digito;
	int factor = 1;
	int posicion = 0;

	while (num_aux > 9)
	{
		num_aux = num_aux / 10;
		num_digitos++;
	}

	while (numero > 9)
	{
		factor = 1;

		//Calculamos el factor
		for (int i = num_digitos - 1; i > 0; i--)
			factor *= 10;

		ultimo_digito = numero / factor;
		numero = numero % factor;

		array[posicion] = ultimo_digito + '0';
		posicion++;
		num_digitos--;
	}

	array[posicion] = numero + '0';
}

string UtilidadesTipos::LongToString(unsigned long long numero)
{
	string resultado;
	unsigned long long num_aux = numero;
	int num_digitos = 1;
	int ultimo_digito;
	int factor = 1;
	int posicion = 0;

	while (num_aux > 9)
	{
		num_aux = num_aux / 10;
		num_digitos++;
	}

	while (numero > 9)
	{
		factor = 1;

		//Calculamos el factor
		for (int i = num_digitos - 1; i > 0; i--)
			factor *= 10;

		ultimo_digito = numero / factor;
		numero = numero % factor;

		resultado += ultimo_digito + '0';
		posicion++;
		num_digitos--;
	}

	resultado += numero + '0';

	return resultado;
}
