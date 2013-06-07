/*
 * Usuario.cpp
 *
 *  Created on: 26/05/2013
 *      Author: k3rnel
 */

#include "Usuario.h"

Usuario::Usuario() {}

Usuario::Usuario(string nombre, string password, bool es_super_usuario)
{
	this->nombre = nombre;
	this->password = password;
	this->super_usuario = es_super_usuario;
}

Usuario::~Usuario() {}

void Usuario::SetPermisoLectura(string ruta)
{
	this->permisos_lectura.push_back(ruta);
}

void Usuario::SetPermisoEscritura(string ruta)
{
	this->permisos_escritura.push_back(ruta);
}

bool Usuario::ComprobarPermisoEscritura(string ruta)
{
	bool tiene_permiso = false;

	for (unsigned int i = 0; i < permisos_escritura.size(); i++)
	{
		if (permisos_escritura[i] == ruta)
			tiene_permiso = true;
	}

	return tiene_permiso;
}

bool Usuario::ComprobarPermisoLectura(string ruta)
{
	bool tiene_permiso = false;

	for (unsigned int i = 0; i < permisos_lectura.size(); i++)
	{
		if (permisos_lectura[i] == ruta)
			tiene_permiso = true;
	}

	return tiene_permiso;
}

bool Usuario::GetPermisosEscritura(vector<string> &vector)
{
	bool ok = false;

	if (this->permisos_escritura.size() != 0)
		vector = this->permisos_escritura;

	return ok;
}

bool Usuario::GetPermisosLectura(vector<string> &vector)
{
	bool ok = false;

	if (this->permisos_lectura.size() != 0)
		vector = this->permisos_lectura;

	return ok;
}

void Usuario::SetSuperUsuario(bool es_super_usuario)
{
	this->super_usuario = es_super_usuario;
}

bool Usuario::GetSuperUsuario()
{
	return this->super_usuario;
}
