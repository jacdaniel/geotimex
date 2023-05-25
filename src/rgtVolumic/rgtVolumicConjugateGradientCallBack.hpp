

#ifndef __RGTVOLUMICCONJUGATEGRADIENTHPP__
#define __RGTVOLUMICCONJUGATEGRADIENTHPP__

#include <stdio.h>
#include <string.h>
#include <omp.h>
#include <leakyIntegration.hpp>
#include <rgtVolumicConjugateGradientCallBack.h>

template <typename T> RgtVolumicConjugateGradientCallBack<T>::RgtVolumicConjugateGradientCallBack()
{

}

template <typename T> RgtVolumicConjugateGradientCallBack<T>::~RgtVolumicConjugateGradientCallBack()
{

}



template <typename T> void RgtVolumicConjugateGradientCallBack<T>::callBack(void* in, void* out)
{
	T* pOut = (T*)out;
	T* pIn = (T*)in;
// #pragma omp parallel for
	for (int z = 0; z < m_size[2]; z++)
	{
		for (int y = 0; y < m_size[1]; y++)
		{
			for (int x = 0; x < m_size[0]; x++)
			{
				pOut[(long)m_size[0] * m_size[1] * z + (long)m_size[0] * y + x] = opDirect(pIn, x, y, z);
			}
		}
	}
}

template <typename T> void RgtVolumicConjugateGradientCallBack<T>::preconditionner(void* in, void* out)
{
	if (m_leakyIntegrator)
	{
		// fprintf(stderr, "leaky\n");
		m_leakyIntegrator->run((T*)in, (T*)out);
	}
	else
	{
		memcpy(out, in, m_size0 * sizeof(T));
	}
}

template <typename T> void RgtVolumicConjugateGradientCallBack<T>::getTauInit(T* data)
{
	for (int z = 0; z < m_size[2]; z++)
	{
		for (int y = 0; y < m_size[1]; y++)
		{
			for (int x = 0; x < m_size[0]; x++)
			{
				data[(long)m_size[0] * m_size[1] * z + (long)m_size[0] * y + x] = (T)x;
			}
		}
	}
}

template <typename T> void RgtVolumicConjugateGradientCallBack<T>::tauToS(T* data)
{
	for (int z = 0; z < m_size[2]; z++)
	{
		for (int y = 0; y < m_size[1]; y++)
		{
			for (int x = 0; x < m_size[0]; x++)
			{
				data[(long)m_size[0] * m_size[1] * z + (long)m_size[0] * y + x] -= (T)x;
			}
		}
	}
}

template <typename T> void RgtVolumicConjugateGradientCallBack<T>::sToTau(T* data)
{
	for (int z = 0; z < m_size[2]; z++)
	{
		for (int y = 0; y < m_size[1]; y++)
		{
			for (int x = 0; x < m_size[0]; x++)
			{
				data[(long)m_size[0] * m_size[1] * z + (long)m_size[0] * y + x] += (T)x;
			}
		}
	}
}
template <typename T> void RgtVolumicConjugateGradientCallBack<T>::getRhs(T* data)
{
	memset(data, 0, (size_t)m_size[0] * m_size[1] * m_size[2] * sizeof(T));
	for (int z = 0; z < m_size[2]; z++)
	{			
		for (int y = 0; y < m_size[1]; y++)
		{
			for (int x = 0; x < m_size[0]; x++)
			{
				//					if ( mask2D_[(long)size[1]*z+y] != 0 )
				data[(long)m_size[0] * m_size[1] * z + (long)m_size[0] * y + x] = rhsValue(x, y, z);
			}
		}
	}
}

template <typename T> double RgtVolumicConjugateGradientCallBack<T>::getCrit(T* data)
{
	double val = 0.0;
	for (int z = 0; z < m_size[2]; z++)
	{
		for (int y = 0; y < m_size[1]; y++)
		{
			for (int x = 0; x < m_size[0]; x++)
			{
				val += (double)critVal(data, x, y, z);
			}
		}
	}
	return val / (double)m_size0;
}



template <typename T> T RgtVolumicConjugateGradientCallBack<T>::rhsValue(int x, int y, int z)
{
	double val = 0.0;
	double vxy = 0.0, vxz = 0.0, vy = 0.0, vz = 0.0;
	long add0 = (long)m_size[0] * m_size[1] * z + (long)m_size[0] * y + (long)x;
	const double c = 1.0/m_dipFactor;
	const double c2 = 1.0/m_dipFactor2;
	short* dipxy = (short*)m_dipxy;
	short* dipxz = (short*)m_dipxz;

	double w0 = 1.0; // GET_MASK_VALUE(dipxy, dipxz, mask2D, size, x, y, z, w0)
	double wx1 = 1.0; // GET_MASK_VALUE(dipxy, dipxz, mask2D, size, x - 1, y, z, wx1)
	double wy1 = 1.0; // GET_MASK_VALUE(dipxy, dipxz, mask2D, size, x, y - 1, z, wy1)
	double wz1 = 1.0; // GET_MASK_VALUE(dipxy, dipxz, mask2D, size, x, y, z - 1, wz1)
	if (w0 == 0.0 && wx1 == 0.0 && wy1 == 0.0 && wz1 == 0) return (T)0.0;


	if ( m_size[1] > 1 && dipxy != nullptr )
	{
		if (y == 0)
		{
			vy = -dipxy[add0] * w0;
		}
		else if (y == m_size[1] - 1)
		{
			vy = dipxy[add0 - m_size[0]] * w0;
		}
		else
		{
			vy = -dipxy[add0] * w0 + dipxy[add0 - m_size[0]] * wy1;
		}

		if (x == 0)
		{
			vxy = -(double)dipxy[add0] * dipxy[add0] * w0;
		}
		else if (x == m_size[0] - 1)
		{
			vxy = (double)dipxy[add0 - 1] * dipxy[add0 - 1] * wx1;
		}
		else
		{
			vxy = -(double)dipxy[add0] * dipxy[add0] * w0 + (double)dipxy[add0 - 1] * dipxy[add0 - 1] * wx1;
		}
	}
	if ( m_size[2] > 1 && dipxz != nullptr)
	{
		if (z == 0)
		{
			vz = -dipxz[add0] * w0;
		}
		else if (z == m_size[2] - 1)
		{
			vz = dipxz[add0 - (long)m_size[0] * m_size[1]] * wz1;
		}
		else
		{
			vz = -dipxz[add0] * w0 + dipxz[add0 - (long)m_size[0] * m_size[1]] * wz1;
		}
		if (x == 0)
		{
			vxz = -(double)dipxz[add0] * dipxz[add0] * w0;
		}
		else if (x == m_size[0] - 1)
		{
			vxz = (double)dipxz[add0 - 1] * dipxz[add0 - 1] * wx1;
		}
		else
		{
			vxz = -(double)dipxz[add0] * dipxz[add0] * w0 + (double)dipxz[add0 - 1] * dipxz[add0 - 1] * wx1;
		}
	}
	val = -(vxy * c2 + vxz * c2 + vy * c + vz * c);
	return (T)val;
}


#define NABLA2_X(data, size, x0, y0, z0, val) { \
		long add0 = (long)size[0]*size[1]*z0+(long)size[0]*y0+(long)x0; \
		if ( x0 != size[0]-1 ) val = data[add0+1]-data[add0]; else val = 0.0; }

#define NABLA2_Y(data, size, x0, y0, z0, val) { \
		long add0 = (long)size[0]*size[1]*z0+(long)size[0]*y0+(long)x0; \
		if ( y0 != size[1]-1 ) val = data[add0+(long)size[0]]-data[add0]; else val = 0.0; }

#define NABLA2_Z(data, size, x0, y0, z0, val) { \
		long add0 = (long)size[0]*size[1]*z0+(long)size[0]*y0+(long)x0; \
		if ( z0 != size[2]-1 ) val = data[add0+(long)size[0]*size[1]]-data[add0]; else val = 0.0; }


template <typename T> T RgtVolumicConjugateGradientCallBack<T>::opDirect(T* data, int x, int y, int z)
{
	double val = 0.0;
	double nablax0 = 0.0, nablay0 = 0.0, nablaz0 = 0.0;
	double nablax_x1 = 0.0;
	const long add0 = (long)m_size[0] * m_size[1] * z + (long)m_size[0] * y + (long)x;
	const double c = 1.0/m_dipFactor;
	const double c2 = 1.0/m_dipFactor2;
	double A0 = 0.0, Ay1 = 0.0, Ax1 = 0.0;
	double B0 = 0.0, Bz1 = 0.0, Bx1 = 0.0;
	double C0 = 0.0, Cx1 = 0.0;
	double val1 = 0.0, val2 = 0.0, val3 = 0.0;
	short* dipxy = (short*)m_dipxy;
	short* dipxz = (short*)m_dipxz;

	double w0 = 1.0; // GET_MASK_VALUE(dipxy, dipxz, mask2D, size, x, y, z, w0)
	double wx1 = 1.0; // GET_MASK_VALUE(dipxy, dipxz, mask2D, size, x - 1, y, z, wx1)
	double wy1 = 1.0; // GET_MASK_VALUE(dipxy, dipxz, mask2D, size, x, y - 1, z, wy1)
	double wz1 = 1.0; // GET_MASK_VALUE(dipxy, dipxz, mask2D, size, x, y, z - 1, wz1)
	if (w0 == 0.0 && wx1 == 0.0 && wy1 == 0.0 && wz1 == 0) return (T)0.0;

	double AA1 = 0.0, AA2 = 0.0, BB1 = 0.0, BB2 = 0.0, CC1 = 0.0;

	// A0
	NABLA2_X(data, m_size, x, y, z, nablax0)
	if (x > 0)
	{
		NABLA2_X(data, m_size, (x - 1), y, z, nablax_x1)
	}

	if (m_size[1] > 1 && dipxy != nullptr)
	{
		NABLA2_Y(data, m_size, x, y, z, nablay0)
		A0 = nablay0 + (double)dipxy[add0] * c * nablax0;
		if (y > 0)
		{
			NABLA2_X(data, m_size, x, (y - 1), z, val1)
			NABLA2_Y(data, m_size, x, (y - 1), z, val2)
			Ay1 = val2 + (double)dipxy[add0 - m_size[0]] * c * val1;
		}
		if (x > 0)
		{
			NABLA2_Y(data, m_size, (x - 1), y, z, val2)
			Ax1 = val2 + (double)dipxy[add0 - 1] * c * nablax_x1;
		}
		// transpose
		A0 *= w0;
		Ay1 *= wy1;
		Ax1 *= wx1;
		if (y == 0) { AA1 = -A0; }
		else if (y == m_size[1] - 1) { AA1 = Ay1; }
		else { AA1 = -A0 + Ay1; }

		if (x == 0) { AA2 = -A0 * dipxy[add0] * c; }
		else if (x == m_size[0] - 1) { AA2 = Ax1 * dipxy[add0 - 1] * c; }
		else { AA2 = -A0 * dipxy[add0] * c + Ax1 * dipxy[add0 - 1] * c; }
	}

	if (m_size[2] > 1 && dipxz != nullptr)
	{
		NABLA2_Z(data, m_size, x, y, z, val2)
		B0 = val2 + (double)dipxz[add0] * c * nablax0;
		if (z > 0)
		{
			NABLA2_X(data, m_size, x, y, (z - 1), val1)
			NABLA2_Z(data, m_size, x, y, (z - 1), val2)
			Bz1 = val2 + (double)dipxz[add0 - (long)m_size[0] * m_size[1]] * c * val1;
		}
		if (x > 0)
		{
			NABLA2_Z(data, m_size, (x - 1), y, z, val2)
			Bx1 = val2 + (double)dipxz[add0 - 1] * c * nablax_x1;
		}
		// transpose
		B0 *= w0;
		Bx1 *= wx1;
		Bz1 *= wz1;
		if (z == 0) { BB1 = -B0; }
		else if (z == m_size[2] - 1) { BB1 = Bz1; }
		else { BB1 = -B0 + Bz1; }

		if (x == 0) { BB2 = -B0 * dipxz[add0] * c; }
		else if (x == m_size[0] - 1) { BB2 = Bx1 * dipxz[add0 - 1] * c; }
		else { BB2 = -B0 * dipxz[add0] * c + Bx1 * dipxz[add0 - 1] * c; }

	}
	// C
	C0 = nablax0 * m_epsilon;
	if (x > 0)
	{
		Cx1 = nablax_x1 * m_epsilon;
	}
	// transpose
	if (x == 0) { CC1 = -C0; }
	else if (x == m_size[0] - 1) { CC1 = Cx1; }
	else { CC1 = -C0 + Cx1; }
	CC1 = CC1 * m_epsilon;

	val = AA1 + AA2 + BB1 + BB2 + CC1;

	return val;
}


template <typename T> double RgtVolumicConjugateGradientCallBack<T>::critVal(T* data, int x, int y, int z)
{
	T val = (T)0.0;
	double dx = 0.0;
	double dy = 0.0;
	double dz = 0.0;
	short* dipxy = (short*)m_dipxy;
	short* dipxz = (short*)m_dipxz;
	long add0 = (long)m_size[0] * m_size[1] * z + (long)m_size[0] * y + x;
	NABLA2_X(data, m_size, x, y, z, dx)
	if (m_size[1] > 1 && m_dipxy != nullptr)
	{
		double dipy0 = (double)dipxy[add0] * m_invDipFactor;
		NABLA2_Y(data, m_size, x, y, z, dy);
		double val0 = dy + dipy0 * dx + dipy0;
		val += val0 * val0;
	}
	if (m_size[2] > 1 && m_dipxz != nullptr)
	{
		double dipz0 = (double)dipxz[add0] * m_invDipFactor;
		NABLA2_Z(data, m_size, x, y, z, dz)
		double val0 = dz + dipz0 * dx + dipz0;
		val += val0 * val0;
	}
	val += m_epsilon2 * dx * dx;
	return val;
}

/*
template <typename T> double RgtVolumicConjugateGradientCallBack<T>::critVal(T* data, int x, int y, int z)
{
	T val = (T)0.0;
	double dx = 0.0;
	double dy = 0.0;
	double dz = 0.0;
	short* dipxy = (short*)m_dipxy;
	short* dipxz = (short*)m_dipxz;
	long add0 = (long)m_size[0] * m_size[1] * z + (long)m_size[0] * y + x;
	NABLA2_X(data, m_size, x, y, z, dx)
	// if (x < m_size[0] - 1) dx+=1.0;
	if (m_size[1] > 1 && m_dipxy != nullptr)
	{
		NABLA2_Y(data, m_size, x, y, z, dy);
		double dipy = 0.0;
		double dipy0 = (double)dipxy[add0] * m_invDipFactor;
		if ( dx != 0.0 ) dipy = -dy / dx;
		val += (dipy - dipy0) * (dipy - dipy0);
	}
	if (m_size[2]>1 && m_dipxz != nullptr)
	{
		NABLA2_Z(data, m_size, x, y, z, dz)
		double dipz = 0.0;
		double dipz0 = (double)dipxz[add0] * m_invDipFactor;
		if (dx != 0.0) dipz = -dz / dx;
		val += (dipz - dipz0) * (dipz - dipz0);
	}
	return val;
}
*/

#endif