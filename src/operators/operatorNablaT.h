
#ifndef __OPERATORNABLAT__
#define __OPERATORNABLAT__

#include <operatorNablaT.hpp>

class OperatorNablaT
{
public:
	static void NablaTX(float* dataIn, int* size, float* dataOut);
	static void NablaTX(double* dataIn, int* size, double* dataOut);

	static void NablaTY(float* dataIn, int* size, float* dataOut);
	static void NablaTY(double* dataIn, int* size, double* dataOut);


};



#endif