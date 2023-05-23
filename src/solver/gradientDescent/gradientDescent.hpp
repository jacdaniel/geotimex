
#ifndef __GRADIENTDESCENT_HPP__
#define __GRADIENTDESCENT_HPP__

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

#include "gradientDescent.h"

template <typename T> GradientDescent<T>::GradientDescent()
{
	/*
	nbIter = 100;
	size0 = 0;
	rhs = nullptr;
	x = nullptr;
	Xrhs.clear();
	Xx.clear();
	param = nullptr;
	this->callback = nullptr;
	int size1[] = { 1, 1, 1 };
	setSize3D(size1);
	*/
}

template <typename T> GradientDescent<T>::~GradientDescent()
{
	// paramRelease();
}


/*
template <typename T> FlagUtil::RET GradientDescent<T>::paramInit()
{
	if (param != nullptr) return FlagUtil::RET::OK;
	FlagUtil::RET ret = FlagUtil::RET::FAIL;
	param = new PARAM();
	if (memoryZ == nullptr)
	{
		param->z = (T*)calloc(m_size0, sizeof(T));
		if (param->z == nullptr) return ret;
	}
	else
		param->z = memoryZ;

	if (memoryR == nullptr)
	{
		param->r = (T*)calloc(m_size0, sizeof(T));
		if (param->r == nullptr) return ret;
	}
	else
		param->r = memoryR;

	if (memoryD == nullptr)
	{
		param->d = (T*)calloc(m_size0, sizeof(T));
		if (param->d == nullptr) return ret;
	}
	else
		param->d = memoryD;

	param->tmp = param->z;
	return FlagUtil::RET::OK;
}

template <typename T> int ConjugateGradient<T>::paramRelease()
{
	return 1;
}
*/

template <typename T> double GradientDescent<T>::dot(T* v1, long size, T* v2)
{
	double d = 0.0;
	for (long add = 0; add < size; add++)
	{
		d += (double)v1[add] * (double)v2[add];
	}
	return d;
}



template <typename T> FlagUtil::RET GradientDescent<T>::run()
{	
	FlagUtil::RET ret = FlagUtil::RET::OK;
	double step = 0.001;
	bool cont = true;
	int iter = 0;

	T* grad = (T*)calloc(m_size0, sizeof(T));

	while (cont)
	{
		if ( iter%5000 == 0)
			fprintf(stderr, "grad descent [%d] %f %f %f\n", iter, x[0], x[1], x[2]);

		m_callback->grad(x, grad);
		for (long i = 0; i < m_size0; i++)
		{
			x[i] -= step * grad[i];
		}
		iter++;
		if (iter > m_nbIter) cont = false;
	}
	free(grad);
	return ret;
}




#endif
