
#ifndef __UTCONJUGATEGRADIENTHPP__
#define __UTCONJUGATEGRADIENTHPP__

#include <string.h>

#include <utConjugateGradientCallBack.h>

template <typename T> UtConjugateGradientCallBack<T>::UtConjugateGradientCallBack()
{

}

template <typename T> UtConjugateGradientCallBack<T>::~UtConjugateGradientCallBack()
{

}



template <typename T> void UtConjugateGradientCallBack<T>::callBack(void* in, void* out)
{
	T* x = (T*)in;
	T* y = (T*)out;

	y[0] = 66.0 * x[0] + 78.0 * x[1] + 91.0 * x[2];
	y[1] = 78.0 * x[0] + 93.0 * x[1] + 110.0 * x[2];
	y[2] = 91.0 * x[0] + 110.0 * x[1] + 133.0 * x[2];
}

template <typename T> void UtConjugateGradientCallBack<T>::preconditionner(void* in, void* out)
{
	memcpy(out, in, m_size0 * sizeof(T));
}


#endif