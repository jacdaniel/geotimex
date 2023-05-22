

#include <operatorNabla.h>




void OperatorNabla::NablaX(float* dataIn, int* size, float* dataOut)
{
	operatorNablaX_Type_I<float>(dataIn, size[0], size[1], size[2], dataOut);
}

void OperatorNabla::NablaX(double* dataIn, int* size, double* dataOut)
{
	operatorNablaX_Type_I<double>(dataIn, size[0], size[1], size[2], dataOut);
}