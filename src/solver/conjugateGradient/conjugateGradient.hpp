#ifndef __CONJUGATEGRADIENTHPP__
#define __CONJUGATEGRADIENTHPP__

// #pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline") //Optimization flags
// #pragma GCC option("arch=native","tune=native","no-zero-upper") //Enable AVX
// #pragma GCC target("avx")  //Enable AVX
// #include <x86intrin.h> //AVX/SSE Extensions
// #include <bits/stdc++.h> //All main STD libraries


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

#include "conjugateGradient.h"

template <typename T> ConjugateGradient<T>::ConjugateGradient()
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

template <typename T> ConjugateGradient<T>::~ConjugateGradient()
{
	// paramRelease();
}

template <typename T> FlagUtil::RET ConjugateGradient<T>::paramInit()
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


template <typename T> double ConjugateGradient<T>::dot(T* v1, long size, T* v2)
{
	double d = 0.0;
	for (long add = 0; add < size; add++)
	{
		d += (double)v1[add] * (double)v2[add];
	}
	return d;
}



template <typename T> FlagUtil::RET ConjugateGradient<T>::run()
{
	double db = 0.0, rho0 = 0.0, rho1 = 0.0, beta = 0.0, denom = 1.0, alphax = 1.0;
	int cont = 1;
	double err = 0.0;
	FlagUtil::RET ret = FlagUtil::RET::OK;

	if (m_nbIter == 0) return ret;
	// m_callback->setIterMax(nbIter);
	// m_callback->setX(x);

	if (paramInit() == FlagUtil::RET::FAIL)
	{
		paramRelease();
		return FlagUtil::RET::FAIL;
	}

	db = dot(rhs, m_size0, rhs);

	memcpy(param->r, rhs, m_size0 * sizeof(T));
	memcpy(param->d, param->z, m_size0 * sizeof(T));

	fprintf(stderr, "cg init callback\n");
	m_callback->callBack(x, param->tmp);


	// param->r : r0
	for (long add = 0; add < m_size0; add++)
	{
		param->r[add] = rhs[add] - param->tmp[add];
	}

	iter = 0;
	// m_callback->setIter(iter);
	fprintf(stderr, "cg init preconditionner start\n");
	m_callback->preconditionner(param->r, param->z);
	fprintf(stderr, "cg init preconditionner end\n");
	rho0 = dot(param->r, m_size0, param->z);
	while (cont)
	{
		fprintf(stderr, "iter: %d\n", iter);
		// callback->setIter(iter);
		// callback->Fonctionnelle(x, iter);

		if (iter == 0)
		{
			memcpy(param->d, param->z, m_size0 * sizeof(T));
		}
		else
		{
			beta = rho0 / rho1;
			for (long add = 0; add < m_size0; add++)
			{
				param->d[add] = param->z[add] + beta * param->d[add];
			}
		}
		// placé ici à cause de param->tmp = param->z avant de la raffraichir
		// fprintf(stderr, "call callBack\n");
		m_callback->callBack(param->d, param->tmp);
		denom = dot(param->d, m_size0, param->tmp);

		if ( abs(denom) < 1e-12) break;
		alphax = rho0 / denom;
		// fprintf(stderr, "%d - alpha: %f - beta: %f - denom: %f\n", iter, alphax, beta, denom);
		if (fabs(alphax) < 1e6 && fabs(alphax) > 1e-6)
		{
			for (long add = 0; add < m_size0; add++)
			{
				x[add] += alphax * param->d[add];
			}

			for (long add = 0; add < m_size0; add++)
			{
				param->r[add] -= alphax * param->tmp[add];
			}

			m_callback->preconditionner(param->r, param->z);

			rho1 = rho0;
			rho0 = dot(param->r, m_size0, param->z);
			if (rho0 == 0.0) cont = 0;
		}
		else
		{
			cont = 0;
		}

		iter++;
		if (iter >= m_nbIter)
		{
			cont = 0;
		}
	}

	return ret;
}

/*
template <typename T> size_t ConjugateGradient<T>::getWorkMemory(size_t size)
{
	return (size_t)4 * size * sizeof(double);
}

template <typename T> void ConjugateGradient<T>::displayParamAllocationError(size_t size)
{
	fprintf(stderr, "Conjugate Gradient Memory Allocation Error\n");
	fprintf(stderr, "Memory needed: %g bytes\n", 4.0 * size * sizeof(double));
}

template <typename T> void ConjugateGradient<T>::setCallback(void* callback, void* data)
{
	this->callback = (CALLBACK*)callback;
}

template <typename T> void ConjugateGradient<T>::setDisplayData(void* displayData)
{
	this->displayData = (DisplayData*)displayData;
}


template <typename T> void ConjugateGradient<T>::setPreconditionner(void* f, void* data)
{
}

template <typename T> void ConjugateGradient<T>::setSize(size_t size)
{
	this->size0 = size;
}

template <typename T> void ConjugateGradient<T>::setRhs(T* rhs)
{
	this->rhs = rhs;
}

template <typename T> void ConjugateGradient<T>::setX(T* x)
{
	this->x = x;
}

template <typename T> void ConjugateGradient<T>::setNbiter(int nbiter)
{
	this->nbIter = nbiter;
}

template <typename T> void ConjugateGradient<T>::setRhs(std::vector<XData> rhs)
{
	this->Xrhs = rhs;
}

template <typename T> void ConjugateGradient<T>::setX(std::vector<XData> x)
{
	this->Xx = x;
}

template <typename T> void ConjugateGradient<T>::setSize3D(int* size)
{
	for (int i = 0; i < 3; i++)
		size3D[i] = size[i];
}

template <typename T> void ConjugateGradient<T>::setDataMemory(T* M1, T* M2, T* M3)
{
	memoryZ = M1;
	memoryR = M2;
	memoryD = M3;
}

template <typename T> void ConjugateGradient<T>::setIhm(Ihm2* p)
{
	pIhm = p;
}

template <typename T> void ConjugateGradient<T>::setMsg0(std::string msg)
{
	msg0 = msg;
}

template <typename T> void ConjugateGradient<T>::setIterDisplayModulo(int val)
{
	iterDisplayModulo = val;
}

template <typename T> int ConjugateGradient<T>::getIter()
{
	return iter;
}

template <typename T> T* ConjugateGradient<T>::getX()
{
	return x;
}

template <typename T> int* ConjugateGradient<T>::getSize3D()
{
	return size3D;
}


template <typename T> int ConjugateGradient<T>::paramInit()
{
	if (param != nullptr) return SUCCESS;
	int ret = FAIL;
	param = new PARAM();
	if (memoryZ == nullptr)
	{
		ret = mallocSafe((void**)&(param->z), size0, sizeof(T)); if (ret != SUCCESS) return FAIL;
	}
	else
		param->z = memoryZ;

	// ret = mallocSafe((void**)&(param->tmp), size0, sizeof(T)); if ( ret != SUCCESS ) return FAIL;
	if (memoryR == nullptr)
	{
		ret = mallocSafe((void**)&(param->r), size0, sizeof(T)); if (ret != SUCCESS) return FAIL;
	}
	else
		param->r = memoryR;

	if (memoryD == nullptr)
	{
		ret = mallocSafe((void**)&(param->d), size0, sizeof(T)); if (ret != SUCCESS) return FAIL;
	}
	else
		param->d = memoryD;

	param->tmp = param->z;
	return SUCCESS;
}

template <typename T> int ConjugateGradient<T>::paramRelease()
{
	if (param == nullptr) return SUCCESS;
	if (memoryZ == nullptr) FREE(param->z)
		// FREE(param->tmp)
		if (memoryR == nullptr) FREE(param->r)
			if (memoryD == nullptr) FREE(param->d)
				delete param;
	param = nullptr;
	return SUCCESS;
}


template <typename T> double ConjugateGradient<T>::dot(T* v1, long size, T* v2)
{
	int N = getNbreThreadsForProcessing();
	double* d = (double*)calloc(N, sizeof(double));
	omp_set_num_threads(N);
#pragma omp parallel for
	for (long add = 0; add < size; add++)
	{
		int tid = omp_get_thread_num();
		d[tid] += (double)v1[add] * (double)v2[add];
	}
	double d0 = 0.0;
	for (int n = 0; n < N; n++)
		d0 += d[n];
	FREE(d)
		return d0;
}

template <typename T> double ConjugateGradient<T>::dot(std::vector<XData> v1, std::vector<XData> v2)
{
	double d = 0.0;

	for (int n = 0; n < v1.size(); n++)
	{
		double* pv1 = (double*)v1[n].getData();
		double* pv2 = (double*)v2[n].getData();
		int* size = v1[n].getSize();
		long size0 = (long)size[0] * size[1] * size[2];
		// d += dot(pv1, size0, pv2);
	}
	return d;
}




*/


#endif
