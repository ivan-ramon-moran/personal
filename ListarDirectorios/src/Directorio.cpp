#include "Directorio.h"

Directorio::Directorio() {}

int Directorio::BorrarFileDir(string path)
{
	int res_operacion;
	DIR *directorioPtr;
	struct dirent *direntPtr;
	string nombre_dir;

	directorioPtr = opendir(path.c_str());


	while ((direntPtr = readdir(directorioPtr)) != NULL)
	{
		//cout << direntPtr->d_name << endl;
		if (direntPtr->d_type == 0x4)
		{

			if (strcmp(direntPtr->d_name,".") != 0 && strcmp(direntPtr->d_name,"..") != 0)
			{
				nombre_dir = direntPtr->d_name;
				cout << BorrarFileDir(path + "/" + nombre_dir);

			}
		}
		else
		{

			cout << path << "/" << nombre_dir<< endl;
			nombre_dir = direntPtr->d_name;
			remove((path + "/" + nombre_dir).c_str());
		}
		remove(path.c_str());
	}

	/*//Borramos el fichero y devolvemos el resultado de la operacion.
	res_operacion = remove(path.c_str());*/

	return 1;
}

int Directorio::CrearDirectorio(string path)
{
	int res_operacion = 0;

	//mkdir(path.c_str(), S_IRWXU) devuelve -1 si ha habido un error y 0 si no ha habido ninguno
	if (mkdir(path.c_str(), S_IRWXU) == -1)
	{
		//En el caso de que haya un error, lo que hacemos es obtenerlo de errno
		res_operacion = errno;
	}

	return res_operacion;
}

int Directorio::RenombrarFileDir(string path_origen, string path_destino)
{
	int res_operacion;

	//Renombramos el fichero y devolvemos el resultado
	res_operacion = rename(path_origen.c_str(), path_destino.c_str());

	return res_operacion;
}

void Directorio::ListarDirectorio(string path, vector<string> &vector)
{
	//Puntero de tipo DIR
	DIR *directorioPtr;
	//struct de tipo dirent
	struct dirent *direntPtr;

	//Abrimos el directorio
	directorioPtr = opendir(path.c_str());

	if (directorioPtr)
	{
		//Mientras haya directorio a listar, los vamos rellenando en el struct.
		while ((direntPtr = readdir(directorioPtr)) != NULL)
		{
			//Añadimos el directorio al vector
			vector.push_back(direntPtr->d_name);
		}
	}
}
