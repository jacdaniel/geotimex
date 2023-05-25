#include "operatorInsert.h"

template <typename T1, typename T2> int OperatorInsert::insertX_(T1* f, int* size, int y0, int z0, T2* g)
{
	for (long x = 0; x < size[0]; x++)
	{
		f[(long)size[0] * size[1] * z0 + size[0] * y0 + x] = (T1)g[x];
	}

	return 0;
}

template <typename T1, typename T2> int OperatorInsert::insertY_(T1* f, int* size, int x0, int z0, T2* g)
{
	for (long y = 0; y < size[1]; y++)
	{
		f[(long)size[0] * size[1] * z0 + size[0] * y + x0] = (T1)g[y];
	}

	return 0;
}

template <typename T1, typename T2> int OperatorInsert::insertZ_(T1* f, int* size, int x0, int y0, T2* g)
{
	for (long z = 0; z < size[2]; z++)
	{
		f[(long)size[0] * size[1] * z + size[0] * y0 + x0] = (T1)g[z];
	}

	return 0;
}


int OperatorInsert::insertX(double* f, int* size, int y0, int z0, double* g)
{
	return insertX_<double, double>(f, size, y0, z0, g);
}

int OperatorInsert::insertY(double* f, int* size, int x0, int z0, double* g)
{
	return insertY_<double, double>(f, size, x0, z0, g);
}
int OperatorInsert::insertZ(double* f, int* size, int x0, int y0, double* g)
{
	return insertZ_<double, double>(f, size, x0, y0, g);
}

int OperatorInsert::insertX(float* f, int* size, int y0, int z0, float* g)
{
	return insertX_<float, float>(f, size, y0, z0, g);
}

int OperatorInsert::insertY(float* f, int* size, int x0, int z0, float* g)
{
	return insertY_<float, float>(f, size, x0, z0, g);
}

int OperatorInsert::insertZ(float* f, int* size, int x0, int y0, float* g)
{
	return insertZ_<float, float>(f, size, x0, y0, g);
}

int OperatorInsert::insertX(double* f, int* size, int y0, int z0, float* g)
{
	return insertX_<double, float>(f, size, y0, z0, g);
}

int OperatorInsert::insertY(double* f, int* size, int x0, int z0, float* g)
{
	return insertY_<double, float>(f, size, x0, z0, g);
}

int OperatorInsert::insertZ(double* f, int* size, int x0, int y0, float* g)
{
	return insertZ_<double, float>(f, size, x0, y0, g);
}

int OperatorInsert::insertX(float* f, int* size, int y0, int z0, double* g)
{
	return insertX_<float, double>(f, size, y0, z0, g);
}

int OperatorInsert::insertY(float* f, int* size, int x0, int z0, double* g)
{
	return insertY_<float, double>(f, size, x0, z0, g);
}

int OperatorInsert::insertZ(float* f, int* size, int x0, int y0, double* g)
{
	return insertZ_<float, double>(f, size, x0, y0, g);
}
