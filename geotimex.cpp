// geotimex.cpp : définit le point d'entrée de l'application.
//

#include <string.h>
#include <test.h>
#include "geotimex.h"

using namespace std;

int main(int argc, char **argv)
{
	cout << "Hello CMake." << endl;
	if (argc < 2) return 0;
	
	if (strcmp(argv[1], "test") == 0)
	{
		test(argc - 1, &argv[1]);
	}


	return 0;
}
