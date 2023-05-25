//#pragma once

#ifndef __OPERATORINSERT__
#define __OPERATORINSERT__


class OperatorInsert
{
public:
	template <typename T1, typename T2> static int insertX_(T1* f, int* size, int y0, int z0, T2* g);
	template <typename T1, typename T2> static int insertY_(T1* f, int* size, int x0, int z0, T2* g);
	template <typename T1, typename T2> static int insertZ_(T1* f, int* size, int x0, int y0, T2* g);

	static int insertX(double* f, int* size, int y0, int z0, double* g);
	static int insertY(double* f, int* size, int x0, int z0, double* g);
	static int insertZ(double* f, int* size, int x0, int y0, double* g);

	static int insertX(float* f, int* size, int y0, int z0, float* g);
	static int insertY(float* f, int* size, int x0, int z0, float* g);
	static int insertZ(float* f, int* size, int x0, int y0, float* g);

	static int insertX(double* f, int* size, int y0, int z0, float* g);
	static int insertY(double* f, int* size, int x0, int z0, float* g);
	static int insertZ(double* f, int* size, int x0, int y0, float* g);


	static int insertX(float* f, int* size, int y0, int z0, double* g);
	static int insertY(float* f, int* size, int x0, int z0, double* g);
	static int insertZ(float* f, int* size, int x0, int y0, double* g);
};



#endif
