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
