//============================================================================
// Name        : Main.cpp
// Author      : K 3 r N e L
// Version     :
// Copyright   : Free Software for free World!!!
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <pthread.h>

using namespace std;

void *Ascendente(void *threadid);
void *Descendente(void *threadid);


int main()
{
	pthread_t thread1, thread2;

	cout << "haaag" << endl;

	pthread_create(&thread1, NULL, Ascendente, (void *)0);
	pthread_create(&thread2, NULL, Descendente,(void *)1);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);


	return 0;
}

void *Ascendente(void *threadid)
{
	clock_t ini, fin;
	int suma = 0;

	ini = clock();

	for (int i = 0; i <= 15000000000; i++)
	{
		suma += i;
	}

	fin = clock();

	cout << "El tiempo del for ascendente es: " << (float)(fin - ini) / CLOCKS_PER_SEC << endl;
}

void *Descendente(void *threadid)
{
	clock_t ini, fin;
	int suma = 0;

	ini = clock();

	for (int i = 1500000000; i >= 0; i--)
	{
		suma += i;
	}

	fin = clock();

	cout << "El tiempo del for descendente es: " << (float)(fin - ini) / CLOCKS_PER_SEC << endl;

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
}
