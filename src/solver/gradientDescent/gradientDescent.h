
#ifndef __GRADIENTDESCENT__
#define __GRADIENTDESCENT__

// #pragma once

#include <flagUtil.h>


template <typename T> class GradientDescentCallBack;


template <typename T> class GradientDescent
{
public:


private:
	long m_nbIter = 10, m_size0 = 0;
	T* b = nullptr;
	T* x = nullptr;
	int size3D[3];
	GradientDescentCallBack<T>* m_callback = nullptr;
	double dot(T* v1, long size, T* v2);

	// FlagUtil::RET paramInit();
	// int paramRelease();
public:
	GradientDescent();
	~GradientDescent();

	void setSize(long size) { m_size0 = size; }
	void setCallback(GradientDescentCallBack<T>* callback) { m_callback = callback; }
	void setNbiter(int nbiter) { m_nbIter = nbiter; }
	void setB(T* v) { rhs = (T*)v; }
	void setX(T* v) { x = (T*)v; }
	FlagUtil::RET run();

};


#endif

