
#include <operatorNablaT.h>


void OperatorNablaT::NablaTX(float* dataIn, int* size, float* dataOut)
{
	operatorNablaTX_Type_I<float>(dataIn, size[0], size[1], size[2], dataOut);
}

void OperatorNablaT::NablaTX(double* dataIn, int* size, double* dataOut)
{
	operatorNablaTX_Type_I<double>(dataIn, size[0], size[1], size[2], dataOut);
}

void OperatorNablaT::NablaTY(float* dataIn, int* size, float* dataOut)
{
	operatorNablaTY_Type_I<float>(dataIn, size[0], size[1], size[2], dataOut);
}

void OperatorNablaT::NablaTY(double* dataIn, int* size, double* dataOut)
{
	operatorNablaTY_Type_I<double>(dataIn, size[0], size[1], size[2], dataOut);
}