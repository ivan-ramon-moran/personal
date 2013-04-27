
#ifndef _PUBLICACION_H
#define _PUBLICACION_H

#include <iostream>
#include <string>
using namespace std;
#include "Fecha.h"

class Publicacion
{
    public:
        Publicacion ();
        void IniciarPublicacion (long long cod, string edi, Fecha fec);
        void PonerCodigo (int);
        void PonerEditor (string);
        void PonerFecha (Fecha& fecha);
        int ConsultarCodigo (void) const;
        string ConsultarEditor (void) const;
        Fecha ConsultarFecha (void) const;
        friend ostream& operator<< (ostream&, Publicacion);

    private:
        long long codigo;
        string editor;
        Fecha fecha;
};

#endif
