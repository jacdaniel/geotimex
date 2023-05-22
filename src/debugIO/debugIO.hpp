

#ifndef __DATAIO_HPP__
#define __DATAIO_HPP__

#include <string>
#include <stdio.h>

template <typename T> void dataSave(std::string filename, T* data, int dimx, int dimy, int dimz)
{
	std::string path = filename + "_" + std::to_string(dimx) + "x" + std::to_string(dimy) + "x" + std::to_string(dimz) + ".raw";
	FILE* pf = fopen(path.c_str(), "w");
	if (pf == nullptr) return;
	fwrite((const void*)data, sizeof(T), (size_t)dimx * dimy * dimz, pf);
	fclose(pf);
}

template <typename T> void dataSave(std::string filename, T* data, int* size)
{
	dataSave<T>(filename,data, size[0], size[1], size[2]);
}


#endif