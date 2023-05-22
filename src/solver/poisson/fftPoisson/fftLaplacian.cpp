

#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>
#include <fftLaplacian.h>


FFTLaplacian::FFTLaplacian()
{

}

FFTLaplacian::~FFTLaplacian()
{

	paramRelease();
}

/*
long x, z, dx, dz;
double* filter = NULL, wx, wz, l1, l2, val;

dx = x2 + 1 - x1;
dz = z2 + 1 - z1;
filter = (double*)CALLOC(dx * dz, double);
for (x = x1; x <= x2; x++)
for (z = z1; z <= z2; z++)
if (x == 0 && z == 0)
filter[0] = 0.0;
else
{
	wx = 2.0 * PI * (double)x / (double)dxt;
	wz = 2.0 * PI * (double)z / (double)dzt;
	l1 = -4.0 + 2.0 * cos(wx) + 2.0 * cos(wz);
	l2 = 20.0 - 16.0 * cos(wx) - 16.0 * cos(wz) + 8.0 * cos(wx) * cos(wz) + 2.0 * cos(2.0 * wx) + 2.0 * cos(2.0 * wz);
	val = l1 - mu * l2 - lambda;
	filter[(z - z1) * dx + x - x1] = 1.0 / val;
}
return filter;
*/

RETURN FFTLaplacian::paramInit1D()
{
	if (param == nullptr || param->invLaplacian == nullptr) return RETURN::FAIL;
	for (int x = 0; x < param->size0; x++)
	{
		double wx = 2.0 * M_PI * (double)x / (double)param->size0 / 2.0;
		double wz = 0.0;
		double l1 = -4.0 + 2.0 * cos(wx) + 2.0 * cos(wz);
		double l2 = 6.0 - 8.0 * cos(wx) + 2.0 * cos(2.0 * wx);
		// l1 = -4.0 + 2.0 * cos(wx) + 2.0 * cos(wz);
		// l2 = 20.0 - 16.0 * cos(wx) - 16.0 * cos(wz) + 8.0 * cos(wx) * cos(wz) + 2.0 * cos(2.0 * wx) + 2.0 * cos(2.0 * wz);
		double val = l1 -vars.mu * l2 - vars.lambda;
		((double*)param->laplacian)[x] = val;
	}
	((double*)param->invLaplacian)[0] = 0.0;
	for (long i = 1; i < param->size0; i++)
	{
		((double*)param->invLaplacian)[i] = 1.0 / ((double*)param->laplacian)[i];
	}
	return RETURN::SUCCESS;
}

RETURN FFTLaplacian::paramInit2D()
{

	return RETURN::SUCCESS;
}

RETURN FFTLaplacian::paramInit3D()
{

	return RETURN::SUCCESS;
}

RETURN FFTLaplacian::paramInit()
{
	if (param != nullptr) return RETURN::SUCCESS;
	param = new PARAM();
	param->size0 = DataUtil::getSize0(vars.size);
	param->dim = DataUtil::getDim(vars.size);
	param->invLaplacian = new double[param->size0];
	// if (param->invLaplacian == nullptr) return RETURN::FAIL;
	param->laplacian = new double[param->size0];
	if (param->laplacian == nullptr) return RETURN::FAIL;
	if (param->dim == DataUtil::DATA_DIM::DIM_1D)
	{
		paramInit1D();
	}
	else if (param->dim == DataUtil::DATA_DIM::DIM_2D)
	{
		paramInit2D();
	}
	else if (param->dim == DataUtil::DATA_DIM::DIM_3D)
	{
		paramInit3D();
	}
	else
	{
		return RETURN::FAIL;
	}
	return RETURN::SUCCESS;
}

RETURN FFTLaplacian::paramRelease()
{

	return RETURN::SUCCESS;
}


RETURN FFTLaplacian::apply(void* data)
{
	if ( vars.m_dataFormat == DATA_FORMAT::FLOAT32 ) return apply0 <float>((float*) data);
	return RETURN::SUCCESS;
}


template <typename T> RETURN FFTLaplacian::apply0(T* data)
{
	for (long add = 0; add < param->size0; add++)
		data[add] /= (T)((double*)param->laplacian)[add];

	return RETURN::SUCCESS;
}


void FFTLaplacian::init()
{
	paramInit();
}

void* FFTLaplacian::getData()
{
	if (!param) return nullptr;
	return param->laplacian;
}

void* FFTLaplacian::getInvData()
{
	if (!param) return nullptr;
	return param->invLaplacian;
}