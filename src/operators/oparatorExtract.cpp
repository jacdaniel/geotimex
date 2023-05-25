
#include "operatorExtract.h"

template <typename T1, typename T2> int OperatorExtract::extractX_(T1* f, int* size, int y0, int z0, T2* g)
{
	for (long x = 0; x < size[0]; x++)
	{
		g[x] = (T2)f[(long)size[0] * size[1] * z0 + size[0] * y0 + x];
	}

	return 0;
}

template <typename T1, typename T2> int OperatorExtract::extractY_(T1* f, int* size, int x0, int z0, T2* g)
{
	for (long y = 0; y < size[1]; y++)
	{
		g[y] = (T2)f[(long)size[0] * size[1] * z0 + size[0] * y + x0];
	}

	return 0;
}

template <typename T1, typename T2> int OperatorExtract::extractZ_(T1* f, int* size, int x0, int y0, T2* g)
{
	for (long z = 0; z < size[2]; z++)
	{
		g[z] = (T2)f[(long)size[0] * size[1] * z + size[0] * y0 + x0];
	}

	return 0;
}


int OperatorExtract::extractX(double* f, int* size, int y0, int z0, double* g)
{
	return extractX_<double, double>(f, size, y0, z0, g);
}

int OperatorExtract::extractY(double* f, int* size, int x0, int z0, double* g)
{
	return extractY_<double, double>(f, size, x0, z0, g);
}
int OperatorExtract::extractZ(double* f, int* size, int x0, int y0, double* g)
{
	return extractZ_<double, double>(f, size, x0, y0, g);
}

int OperatorExtract::extractX(float* f, int* size, int y0, int z0, float* g)
{
	return extractX_<float, float>(f, size, y0, z0, g);
}

int OperatorExtract::extractY(float* f, int* size, int x0, int z0, float* g)
{
	return extractY_<float, float>(f, size, x0, z0, g);
}

int OperatorExtract::extractZ(float* f, int* size, int x0, int y0, float* g)
{
	return extractZ_<float, float>(f, size, x0, y0, g);
}


int OperatorExtract::extractX(double* f, int* size, int y0, int z0, float* g)
{
	return extractX_<double, float>(f, size, y0, z0, g);
}

int OperatorExtract::extractY(double* f, int* size, int x0, int z0, float* g)
{
	return extractY_<double, float>(f, size, x0, z0, g);
}

int OperatorExtract::extractZ(double* f, int* size, int x0, int y0, float* g)
{
	return extractZ_<double, float>(f, size, x0, y0, g);
}


int OperatorExtract::extractX(float* f, int* size, int y0, int z0, double* g)
{
	return extractX_<float, double>(f, size, y0, z0, g);
}

int OperatorExtract::extractY(float* f, int* size, int x0, int z0, double* g)
{
	return extractY_<float, double>(f, size, x0, z0, g);
}

int OperatorExtract::extractZ(float* f, int* size, int x0, int y0, double* g)
{
	return extractZ_<float, double>(f, size, x0, y0, g);
}

int OperatorExtract::extractZ(short* f, int* size, int x0, int y0, short* g)
{
	return extractZ_<short, short>(f, size, x0, y0, g);
}
