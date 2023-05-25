
#ifndef __DEBUGIO__
#define __DEBUGIO__

#include <debugIO.hpp>

// #include <string>

class DebugIO
{
public:
	static void dataPrint(short *data, int dimx, int dimy = 1, int dimz = 1);
	static void dataPrint(double* data, int dimx, int dimy = 1, int dimz = 1);
};


/*
template <typename T> void dataSave(std::string filename, T* data, int dimx, int dimy, int dimz);
template <typename T> void dataSave(std::string filename, T* data, int* size);
*/

#endif