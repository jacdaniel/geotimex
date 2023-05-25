
#ifndef __OPERATOREXTRACT__
#define __OPERATOREXTRACT__



class OperatorExtract
{
public:
	template <typename T1, typename T2> static int extractX_(T1* f, int* size, int y0, int z0, T2* g);
	template <typename T1, typename T2> static int extractY_(T1* f, int* size, int x0, int z0, T2* g);
	template <typename T1, typename T2> static int extractZ_(T1* f, int* size, int x0, int y0, T2* g);

	static int extractX(double* f, int* size, int y0, int z0, double* g);
	static int extractY(double* f, int* size, int x0, int z0, double* g);
	static int extractZ(double* f, int* size, int x0, int y0, double* g);

	static int extractX(float* f, int* size, int y0, int z0, float* g);
	static int extractY(float* f, int* size, int x0, int z0, float* g);
	static int extractZ(float* f, int* size, int x0, int y0, float* g);

	static int extractX(double* f, int* size, int y0, int z0, float* g);
	static int extractY(double* f, int* size, int x0, int z0, float* g);
	static int extractZ(double* f, int* size, int x0, int y0, float* g);

	static int extractX(float* f, int* size, int y0, int z0, double* g);
	static int extractY(float* f, int* size, int x0, int z0, double* g);
	static int extractZ(float* f, int* size, int x0, int y0, double* g);

	// static int extractX(float* f, int* size, int y0, int z0, double* g);
	// static int extractY(float* f, int* size, int x0, int z0, double* g);
	static int extractZ(short* f, int* size, int x0, int y0, short* g);

};


#endif