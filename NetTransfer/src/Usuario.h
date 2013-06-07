#include <iostream>
#include <vector>

using namespace std;

#ifndef USUARIO_H_
#define USUARIO_H_

class Usuario {
public:
	//Contructor
	Usuario();
	//Contructor explícito
	Usuario(string nombre, string password, bool es_super_usuario);

	//Operacion permitidas
	void SetPermisoLectura(string ruta);
	void SetPermisoEscritura(string ruta);
	bool ComprobarPermisoEscritura(string ruta);
	bool ComprobarPermisoLectura(string ruta);
	bool GetPermisosEscritura(vector<string> &vector);
	bool GetPermisosLectura(vector<string> &vector);
	void SetSuperUsuario(bool es_super_usuario);
	bool GetSuperUsuario();

	virtual ~Usuario();

private:
	string nombre, password;
	vector<string> permisos_lectura;
	vector<string> permisos_escritura;
	bool super_usuario;
};

#endif /* USUARIO_H_ */
