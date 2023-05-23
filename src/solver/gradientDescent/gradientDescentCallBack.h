
#ifndef __GRADIENTDESCENTCALLBACK__
#define __GRADIENTDESCENTCALLBACK__

template <typename T> class GradientDescentCallBack
{
public:
	virtual void grad(void* in, void* out) = 0;
	void setSize(long size0) { m_size0 = size0; }


protected:
	long m_size0 = 0;
};


#endif