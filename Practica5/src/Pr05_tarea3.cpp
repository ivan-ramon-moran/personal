/************************** Pr05_tarea3.cpp ************************************
 *
 *  Proposito: Programa que lee un fichero de publicaciones y las muestra
 *             por pantalla
 *
 *  Historial del Desarrollo:
 *  Fecha       Autor              Id Cambio  Version  Descripcion del cambio
 *  ----------  ------------------ ---------  -------  ----------------------
 *  16-04-2013  Ricardo Ferris          0      0.9
 *****************************************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include "Libro.h"
#include "Revista.h"
#include "Publicacion.h"
#include "Fecha.h"
#include <typeinfo>
#include <stdio.h>
#include <iomanip>

using namespace std;

template <class TipoPub>
void MostrarPublicaciones (vector<TipoPub>);

template <class TipoPub>
void FiltrarVector(vector<TipoPub> &vector, Fecha &f_min, Fecha &f_max);

template <class TipoPub>
void QuickSort(vector<TipoPub> &vector, int izquierda, int derecha);

bool LeerPublicacionFichero (ifstream &fichero, Libro &libro, Revista &revista, bool &es_libro);
void MostrarPublicacionesOrdenadas(vector<Libro> &libros, vector<Revista> &revistas);

/*****************************************************************************
 ************************ Programa Principal *********************************
 *****************************************************************************/
int main()
{
    vector<Libro> libros;
    vector<Revista> revistas;
    Libro libro;
    Revista revista;
    ifstream f;
    bool es_libro;
    Fecha f_min, f_max;

    f.open ("Publicaciones02.dat");

    if (!f)
        cout << "Error abriendo fichero de publicaciones";
    else
    {
        while (LeerPublicacionFichero (f, libro, revista, es_libro) )
        {
        	if (es_libro)
        		libros.push_back (libro);
        	else
        		revistas.push_back(revista);
        }
    }

    //Preguntamos las fechas.
	//Fecha mínima
	cout << "Introduce la fecha minima [dia/mes/anyo]: ";
	cin >> f_min;

	//Fecha máxima
	cout << "Introduce la fecha maxima [dia/mes/anyo]: ";
	cin >> f_max;

	//Filtramos los vectores por fecha
	FiltrarVector(libros, f_min, f_max);
	FiltrarVector(revistas, f_min, f_max);

	//Ordenamos los vectores
	QuickSort(libros, 0, libros.size() - 1);
	QuickSort(revistas, 0, revistas.size() - 1);

	//Una vez tenemos los 2 vectores ordenados mostramos los resultados
	MostrarPublicacionesOrdenadas(libros, revistas);

    return 0;
}

/***** MostrarPublicaciones **************************************************
 *
 * Prototipo:
 *     void MostrarPublicaciones (vector<Publicacion> publicaciones)
 *
 * Proposito:
 *  Mostrar todas las publicaciones contenidas en el vector que se le pasa
 *  como parametro
 *
 * Paramatros:
 *  Nombre        Tipo                E/S  Descripcion
 *  ------        ----------          ---  ------------
 *  publicaciones vector<Publicacion> E    Vector de la STL donde se
 *                                         encuentra la informacion a mostrar
 *
 *  Valor devuelto:
 *  Ninguno
 *****************************************************************************/
template <class TipoPub>
void MostrarPublicaciones (vector<TipoPub> publicaciones)
{
	unsigned int i;
	bool son_libros = false;

    if (typeid(publicaciones[0]).name() == typeid(Libro).name())
    {
    	cout << VERDE << "Los libros leidos son:" << BLANCO << endl;
    	//Asignamos al bool son_libros el valor de true ya que son libros
    	son_libros = true;
    }
    else
    	cout  << endl << VERDE << "Las revista leidas son: " << BLANCO << endl;


    for (i = 0; i < publicaciones.size (); i++)
        cout << publicaciones[i];

    cout << endl << ROJO << "Se han ledio un total de " << publicaciones.size () << BLANCO;

    if (son_libros)
    	cout << ROJO << " libros." << BLANCO << endl;
    else
    	cout << ROJO << " revistas." << BLANCO << endl;

    return;
}

/***** LeerPublicacionFichero ************************************************
 *
 * Prototipo:
 *     bool LeerPublicacionFichero (ifstream & f, Publicacion & publicacion)
 *
 * Proposito:
 *  Leer del fichero f un objeto del tipo publicacion (codigo, fecha y
 *  editorial) y devolver el objeto leido.
 *
 * Paramatros:
 *  Nombre        Tipo                E/S  Descripcion
 *  ------        ----------          ---  ------------
 *  f             ifstream            E S  Fichero del que leer
 *  publicacion   Publicacion           S  Variable a traves de la que se
 *                                         devuelve la informacion leida
 *
 *  Valor devuelto:
 *  bool  true si la informacion ha sido leida correctamente
 *        false si la informacion NO se ha podido leer de forma correcta
 *****************************************************************************/
bool LeerPublicacionFichero (ifstream &f, Libro &libro, Revista &revista, bool &es_libro)
{
    bool ok;
    long long codigo;
    string editorial, autor, titulo, periodicidad;
	Fecha fecha;
	int num_ejemplar;

	es_libro = false;

    if (f >> codigo)
    {
    	if (codigo == 1)
    	{
    		//Leemos la fecha
    		f >> fecha;
    		//Leemos la editorial
    		getline(f, editorial);
    		//Leemos el titulo
    		getline(f, titulo);
    		//Leemos el autor
    		getline(f, autor);

    		//Creamos el objeto libro
    		libro.IniciarLibro(codigo, editorial, fecha, titulo, autor);

    		//Devolvemos la variable que indica que es un libro para saber en que vector añadirlo.
    		es_libro = true;
    	}
    	else
    	{
    		//Leemos la fecha
			f >> fecha;
			//Leemos la editorial
			getline(f, editorial);
			//Leemos el titulo
			getline(f, titulo);
			//Leemos la periodicidad
			getline(f, periodicidad);
			//Leemos el numero de ejemplar
			f >> num_ejemplar;

			//Creamos el objeto Revista
			revista.IniciarRevista(codigo, editorial, fecha, titulo, periodicidad, num_ejemplar);
    	}

    	ok = true;

    }
    else
        ok = false;

    return ok;
}

template <class TipoPub>
void FiltrarVector(vector<TipoPub> &vector, Fecha &f_min, Fecha &f_max)
{
	for (unsigned int i = 0; i < vector.size(); i++)
	{
		Fecha f = vector[i].ConsultarFecha();

		if (!((f < f_max) && (f > f_min)))
		{
			vector.at(i) = vector.back();
			vector.pop_back();
			i--;
		}
	}
}

template <class TipoPub>
void QuickSort(vector<TipoPub> &vector, int izquierda, int derecha)
{
	int i, j, pivote;

	i = izquierda;
	j = derecha;
	pivote = (izquierda + derecha) / 2;

	while (i <= j)
	{
		while (vector[i].GetTitulo() < vector[pivote].GetTitulo())
			i++;

		while (vector[j].GetTitulo() > vector[pivote].GetTitulo())
			j--;

		if (i < j)
		{
			TipoPub pub_aux = vector[i];
			vector.at(i) = vector[j];
			vector.at(j) = pub_aux;
			i++;
			j--;
		}
		else
		{
			if (i == j)
			{
				i++;
				j--;
			}
		}
	}

	if (izquierda < j)
		QuickSort (vector, izquierda, j);
	if (i < derecha)
		QuickSort (vector, i, derecha);
}

void MostrarPublicacionesOrdenadas(vector<Libro> &libros, vector<Revista> &revistas)
{
	unsigned int i, j;

	i=j=0;

	while (i < libros.size() && j < revistas.size())
	{
		if (libros[i].GetTitulo() < revistas[j].GetTitulo())
		{
			cout << libros[i] << endl;
			i++;
		}
		else
		{
			cout << revistas[j] << endl;
			j++;
		}
	}

	if (i != libros.size())
	{
		while (i < libros.size())
		{
			cout << libros[i] << endl;
			i++;
		}
	}

	if (j != revistas.size())
	{
		while (j < revistas.size())
		{
			cout << revistas[j] << endl;
			j++;
		}
	}
}
