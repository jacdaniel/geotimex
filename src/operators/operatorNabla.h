
#ifndef __OPERATORNABLA__
#define __OPERATORNABLA__

#include <operatorNabla.hpp>

class OperatorNabla
{
public:
	static void NablaX(float* dataIn, int* size, float* dataOut);
	static void NablaX(double* dataIn, int* size, double* dataOut);
	

};



#endif