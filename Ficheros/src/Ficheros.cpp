#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream f_ent;
	ofstream f_sal;
	int numero = 3;

	f_sal.open("file.data", ios::binary);

	if (f_sal)
	{
		f_sal.write((char *)&numero, sizeof(int));
		f_sal.close();
	}

	numero = 0;

	f_ent.open("file.data", ios::binary);

	if (f_ent)
	{
		f_ent.read((char *)&numero, sizeof(int));
		f_ent.close();
	}

	cout << numero << endl;
	return 0;
}
