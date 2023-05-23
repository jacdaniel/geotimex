

#ifndef __UTGRADEINTDESCENTHPP__
#define __UTGRADIENTDESCENTHPP__

#include <string.h>

#include <utGradientDescentCallBack.h>

template <typename T> UtGradientDescentCallBack<T>::UtGradientDescentCallBack()
{

}

template <typename T> UtGradientDescentCallBack<T>::~UtGradientDescentCallBack()
{

}



template <typename T> void UtGradientDescentCallBack<T>::grad(void* in, void* out)
{
	T* x = (T*)in;
	T* y = (T*)out;

	y[0] = 66.0 * x[0] + 78.0 * x[1] + 91.0 * x[2] - 1460;
	y[1] = 78.0 * x[0] + 93.0 * x[1] + 110.0 * x[2] - 1750;
	y[2] = 91.0 * x[0] + 110.0 * x[1] + 133.0 * x[2] - 2088;
}


#endif
