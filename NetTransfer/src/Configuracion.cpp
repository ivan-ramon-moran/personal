#include "Configuracion.h"

Configuracion::Configuracion()
{
	mostrar_archivos_ocultos = false;
}

Configuracion* Configuracion::instance = 0;// Inicializar el puntero

Configuracion* Configuracion::get_instance()
{
	if (instance == 0)
		instance = new Configuracion();

	return instance;
}
