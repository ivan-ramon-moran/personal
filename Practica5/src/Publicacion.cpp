
#include "Publicacion.h"
#include "Fecha.h"

Publicacion::Publicacion ()
{
    codigo = 0;
}

void Publicacion::IniciarPublicacion (long long cod, string edi, Fecha fec)
{
    codigo = cod;
    editor = edi;
    fecha = fec;

    return;   
}

void Publicacion::PonerCodigo (int cod)
{
    codigo = cod;
    
    return;
}

void Publicacion::PonerEditor (string edi)
{
    editor = edi;
    
    return;
}

void Publicacion::PonerFecha (Fecha &fec)
{
    fecha = fec;

    return;
}

int Publicacion::ConsultarCodigo (void) const
{
    return codigo;
}

string Publicacion::ConsultarEditor (void) const
{
    return editor;
}

Fecha Publicacion::ConsultarFecha (void) const
{
    return fecha;
}

ostream& operator<< (ostream& out, Publicacion pub)
{
    out << "Codigo y fecha: " << pub.codigo << '\t';
    out << pub.fecha << endl;    
    out << "Editorial: " << pub.editor << endl;

    return out;
}
