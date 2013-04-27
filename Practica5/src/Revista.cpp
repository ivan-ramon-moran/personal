#include "Revista.h"
#include "Libro.h"

Revista::Revista() {}

void Revista::IniciarRevista(long long codigo, string editor, Fecha &fecha, string titulo, string periodicidad, int num_ejemplar)
{
	//Atributos de la clase base mediante sus metodos publicos
	PonerCodigo(codigo);
	PonerEditor(editor);
	PonerFecha(fecha);

	//Atributos propios de la clase
	this->titulo = titulo;
	this->periodicidad = periodicidad;
	this->num_ejemplar = num_ejemplar;
}

//Getters y Setters

string Revista::GetTitulo()
{
	return this->titulo;
}

void Revista::SetTitulo(string titulo)
{
	this->titulo = titulo;
}

string Revista::GetPeriodicidad() const
{
	return this->periodicidad;
}

void Revista::SetPeriodicidad(string periodicidad)
{
	this->periodicidad = periodicidad;
}

int Revista::GetNumEjemplar() const
{
	return this->num_ejemplar;
}

void Revista::SetNumEjemplar(int num_ejemplar)
{
	this->num_ejemplar = num_ejemplar;
}

ostream& operator<<(ostream &out, const Revista &revista)
{
	out << AZUL << "Tipo: Revista" << endl;
	out << endl << AMARILLO << "Titulo: " << BLANCO << revista.titulo << endl;
	out << AMARILLO << "Periodicidad: " << BLANCO << revista.periodicidad << endl;
	cout << AMARILLO << "Numero: " << BLANCO << revista.num_ejemplar << endl;
	out << AMARILLO << "Editor: " << BLANCO << revista.ConsultarEditor() << endl;
	out << AMARILLO << "Fecha de publicacion: " << BLANCO << revista.ConsultarFecha() << endl;

	return out;
}
