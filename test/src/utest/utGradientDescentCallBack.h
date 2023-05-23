
#include <gradientDescentCallBack.h>

#ifndef __UTGRADIENTDESCENT__
#define __UTGRADIENTDESCENT__


template <typename T> class UtGradientDescentCallBack : public GradientDescentCallBack<T>
{
public:
	UtGradientDescentCallBack();
	virtual ~UtGradientDescentCallBack();

	void grad(void* in, void* out);
};



#endif