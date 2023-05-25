
#ifndef __LEAKYINTEGRATIONHPP__
#define __LEAKYINTEGRATIONHPP__

#include <malloc.h>

#include <omp.h>

#include <algorithm>
#include <operatorExtract.h>
#include <operatorInsert.h>
#include <LeakyIntegration.h>


template <typename T> LeakyIntegration<T>::LeakyIntegration()
{
	// nbThreads = getNbreThreadsForProcessing();
}

template <typename T> LeakyIntegration<T>::~LeakyIntegration()
{
	paramRelease();
}


template <typename T> int LeakyIntegration<T>::paramInit()
{
	if (param != nullptr) return 1;
	param = new PARAM();
	param->e = (double**)calloc(3, sizeof(double*));
	param->t = (double**)calloc(3, sizeof(double*));
	param->w = (double**)calloc(3, sizeof(double*));
	for (int n = 0; n < 3; n++)
	{
		param->e[n] = (double*)calloc(static_cast<size_t>(size[n] + 1), sizeof(double));
		param->t[n] = (double*)calloc(static_cast<size_t>(size[n] + 1), sizeof(double));
		param->w[n] = (double*)calloc(static_cast<size_t>(size[n] + 1), sizeof(double));
		int c = -this->c;
		for (int i1 = 1; i1 < size[n]; ++i1)
		{
			param->e[n][i1] = c;
			param->w[n][i1] = c;
		}

		param->t[n][0] = 1.0f - param->e[n][0] - param->e[n][1];
		double di, ei;
		for (int i1 = 1; i1 < size[n]; ++i1)
		{
			di = 1.0f - param->e[n][i1] - param->e[n][i1 + 1];
			ei = param->e[n][i1];
			param->w[n][i1] = ei / param->t[n][i1 - 1];
			param->t[n][i1] = di - ei * param->w[n][i1];
		}

		param->sumT[n] = 0.0;
		for (int i = 0; i < size[n]; i++)
			param->sumT[n] += param->t[n][i];
	}
	int sMax = std::max(size[0], size[1]);
	sMax = std::max(sMax, size[2]);

	// todo
	/**
	 *
	 */
	param->v = (T**)calloc(nbThreads, sizeof(T*));
	param->vr = (T**)calloc(nbThreads, sizeof(T*));
	for (int i = 0; i < nbThreads; i++) param->v[i] = (T*)calloc(sMax, sizeof(T));
	for (int i = 0; i < nbThreads; i++) param->vr[i] = (T*)calloc(sMax, sizeof(T));
	return 1;
}

template <typename T> int LeakyIntegration<T>::paramRelease()
{
	if (param == nullptr) return 1;
	for (int i = 0; i < 3; i++)
	{
		free(param->e[i]);
		free(param->t[i]);
		free(param->w[i]);
	}
	free(param->e);
	free(param->t);
	free(param->w);

	for (int i = 0; i < nbThreads; i++) free(param->v[i]);
		free(param->v);
		for (int i = 0; i < nbThreads; i++) free(param->vr[i]);
		free(param->vr);
	delete param;
	param = nullptr;
	return 1;
}

template <typename T> void LeakyIntegration<T>::integration(T* x, int size, double* e, double* t, double* w, T* y, T norm)
{
	int n1 = size;
	y[0] = x[0] / t[0];
	for (int i1 = 1; i1 < n1; ++i1)
	{
		y[i1] = (T)(((double)x[i1] - e[i1] * y[i1 - 1]) / t[i1]);
	}
	for (int i1 = n1 - 1; i1 > 0; --i1)
		y[i1 - 1] -= (T)(w[i1] * y[i1]);
	//TODO
	/**
	 *
	 */
	 // for (int i=0; i<size; i++) y[i] *= norm;
}

template <typename T> void LeakyIntegration<T>::runX(T* in, T* out)
{
	T norm = (T)(param->sumT[0] / (double)size[0]);
	//omp_set_num_threads(nbThreads);
//#pragma omp parallel for
	for (int z = 0; z < size[2]; z++)
	{
		int threadNo = omp_get_thread_num();
		for (int y = 0; y < size[1]; y++)
		{
			OperatorExtract::extractX(in, size, y, z, (T*)param->v[threadNo]);
			integration(param->v[threadNo], size[0], param->e[0], param->t[0], param->w[0], param->vr[threadNo], norm);
			OperatorInsert::insertX(out, size, y, z, (T*)param->vr[threadNo]);
		}
	}
}

template <typename T> void LeakyIntegration<T>::runY(T* in, T* out)
{
	T norm = (T)(param->sumT[1] / (double)size[1]);
	// omp_set_num_threads(nbThreads);
// #pragma omp parallel for
	for (int z = 0; z < size[2]; z++)
	{
		int threadNo = omp_get_thread_num();
		for (int x = 0; x < size[0]; x++)
		{
			OperatorExtract::extractY(in, size, x, z, (T*)param->v[threadNo]);
			integration(param->v[threadNo], size[1], param->e[1], param->t[1], param->w[1], param->vr[threadNo], norm);
			OperatorInsert::insertY(out, size, x, z, (T*)param->vr[threadNo]);
		}
	}
}

template <typename T> void LeakyIntegration<T>::runZ(T* in, T* out)
{
	T norm = (T)(param->sumT[2] / (double)size[2]);
	// omp_set_num_threads(nbThreads);
// #pragma omp parallel for
	for (int y = 0; y < size[1]; y++)
	{
		int threadNo = omp_get_thread_num();
		for (int x = 0; x < size[0]; x++)
		{
			OperatorExtract::extractZ(in, size, x, y, (T*)param->v[threadNo]);
			integration(param->v[threadNo], size[2], param->e[2], param->t[2], param->w[2], param->vr[threadNo], norm);
			OperatorInsert::insertZ(out, size, x, y, (T*)param->vr[threadNo]);
		}
	}
}

template <typename T> void LeakyIntegration<T>::run(T* in, T* out)
{
	paramInit();
	if ( size[0] > 1 ) runX(in, out);
	if ( size[1] > 1 ) runY(out, out);
	if ( size[2] > 1 ) runZ(out, out);
}



#endif
