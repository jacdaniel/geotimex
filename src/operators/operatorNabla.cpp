

#include <operatorNabla.h>




void OperatorNabla::NablaX(float* dataIn, int* size, float* dataOut)
{
	operatorNablaX_Type_I<float>(dataIn, size[0], size[1], size[2], dataOut);
}

void OperatorNabla::NablaX(double* dataIn, int* size, double* dataOut)
{
	operatorNablaX_Type_I<double>(dataIn, size[0], size[1], size[2], dataOut);
}


void  OperatorNabla::NablaY(float* dataIn, int* size, float* dataOut)
{
	operatorNablaY_Type_I<float>(dataIn, size[0], size[1], size[2], dataOut);
}

void  OperatorNabla::NablaY(double* dataIn, int* size, double* dataOut)
{
	operatorNablaY_Type_I<double>(dataIn, size[0], size[1], size[2], dataOut);
}

void  OperatorNabla::NablaZ(float* dataIn, int* size, float* dataOut)
{
	operatorNablaZ_Type_I<float>(dataIn, size[0], size[1], size[2], dataOut);
}

void  OperatorNabla::NablaZ(double* dataIn, int* size, double* dataOut)
{
	operatorNablaZ_Type_I<double>(dataIn, size[0], size[1], size[2], dataOut);
}