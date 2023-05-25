

#ifndef __DATAIO_HPP__
#define __DATAIO_HPP__

#include <string>
#include <stdio.h>

#include <debugIO.h>

template <typename T> void dataSave(std::string filename, T* data, int dimx, int dimy, int dimz)
{
	std::string path = filename + "_" + std::to_string(dimx) + "x" + std::to_string(dimy) + "x" + std::to_string(dimz) + ".raw";
	FILE* pf = fopen(path.c_str(), "wb");
	if (pf == nullptr) return;
	fwrite((const void*)data, sizeof(T), (size_t)dimx * dimy * dimz, pf);
	fclose(pf);
}

template <typename T> void dataSave(std::string filename, T* data, int* size)
{
	// dataSave<T>(filename,(T*)data, size[0], size[1], size[2]);
	std::string path = filename + "_" + std::to_string(size[0]) + "x" + std::to_string(size[1]) + "x" + std::to_string(size[2]) + ".raw";
	FILE* pf = fopen(path.c_str(), "wb");
	if (pf == nullptr) return;
	fwrite((const void*)data, sizeof(T), (size_t)size[0] * size[1] * size[2], pf);
	fclose(pf);
}


#endif