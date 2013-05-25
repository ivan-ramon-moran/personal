#ifndef UTILIDASTIPOS_H_
#define UTILIDASTIPOS_H_

#include <iostream>
#include <string.h>

using namespace std;

class UtilidadesTipos
{
public:
	UtilidadesTipos();

	static string ArrayToString(char *);
	static int ArrayToInt(char array[], int tamanyo);
	static unsigned long long ArrayToLong(char array[], int tamanyo);
	static string IntToString(int numero);
	static void LongToArray(unsigned long long numero, char array[]);
	static void StringToArray(string cadena, char array[]);
	static string ArrayToString(char array[], int tamanyo);
	static string LongToString(unsigned long long numero);

};

#endif /* UTILIDASTIPOS_H_ */
