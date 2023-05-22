
#include <stdio.h>
#include <debugIO.h>

void DebugIO::dataPrint(short* data, int dimx, int dimy, int dimz)
{
	for (long i = 0; i < (long)dimx * dimy * dimz; i++)
		fprintf(stderr, "[%d], %d\n", i, data[i]);
}

void  DebugIO::dataPrint(double* data, int dimx, int dimy, int dimz)
{
	for (long i = 0; i < (long)dimx * dimy * dimz; i++)
		fprintf(stderr, "[%d], %f\n", i, data[i]);
}