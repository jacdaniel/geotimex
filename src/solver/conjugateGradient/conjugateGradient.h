// #pragma once

#ifndef __CONJUGATEGRADIENT__
#define __CONJUGATEGRADIENT__

#include <cstddef>
#include <iostream>
#include <array>

#include<vector>
#include <string>

#include <flagUtil.h>


template <typename T> class ConjugateGradientCallBack;


template <typename T> class ConjugateGradient
{
public:
	
	class PARAM
	{
	public:
		T* tmp = nullptr, * z = nullptr, * r = nullptr, * d = nullptr;
	};


private:
	long m_nbIter = 10, m_size0 = 0;
	T* rhs = nullptr;
	T* x = nullptr;
	int size3D[3];
	// int dataFormat = DATA_FORMAT_DOUBLE;
	int iterDisplayModulo = 1;
	std::string msg0 = "";
	int iter = 0;

	T* memoryZ = nullptr;
	T* memoryR = nullptr;
	T* memoryD = nullptr;



	ConjugateGradientCallBack<T>* m_callback = nullptr;
	double dot(T* v1, long size, T* v2);

	FlagUtil::RET paramInit();

	int paramRelease();
public:
	ConjugateGradient();
	~ConjugateGradient();
	
	void setSize(long size) { m_size0 = size; }
	void setSize3d(int* size) { for (int i = 0; i < 3; i++) size3D[i] = size[i]; }
	void setCallback(ConjugateGradientCallBack<T> *callback) { m_callback = callback; }
	void setNbiter(int nbiter) { m_nbIter = nbiter;  }
	void setRhs(T* v) { rhs = (T*)v; }
	void setX(T* v) { x = (T*)v; }





	static size_t getWorkMemory(size_t size);

	void displayParamAllocationError(size_t size);
	// void setCallback(void* callback, void* data);
	void setDisplayData(void* displayData);
	void setPreconditionner(void* f, void* data);
	void setSize3D(int* size);
	void setDataMemory(T* M1, T* M2, T* M3);
	void setIterDisplayModulo(int val);
	void setMsg0(std::string msg);
	int getIter();

	T* getX();
	int* getSize3D();


	FlagUtil::RET run();

	PARAM* param = nullptr;
};


#endif
