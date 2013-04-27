#include "Libro.h"

Libro::Libro() {}

void Libro::IniciarLibro(long long codigo, string editor, Fecha &fecha, string titulo, string autor)
{
	//Metodos set de la clase base
	PonerCodigo(codigo);
	PonerEditor(editor);
	PonerFecha(fecha);

	//Atributos propios de Libro
	this->autor = autor;
	this->titulo = titulo;
}

//Getters y Setters

string Libro::GetAutor() const
{
	return this->autor;
}

void Libro::SetAutor(string autor)
{
	this->autor = autor;
}

string Libro::GetTitulo() const
{
	return this->titulo;
}

void Libro::SetTitulo(string titulo)
{
	this->titulo = titulo;
}

ostream& operator<< (ostream &out, const Libro &libro)
{
	out << VERDE << "Tipo: Libro" << endl;
	out << endl << AMARILLO << "Titulo: " << BLANCO << libro.titulo << endl;
	out << AMARILLO << "Autor: " << BLANCO << libro.autor << endl;
	out << AMARILLO << "Editorial: " << BLANCO << libro.ConsultarEditor() << endl;
	out << AMARILLO << "Fecha de publicacion: " << BLANCO << libro.ConsultarFecha() << endl;

	return out;
}
