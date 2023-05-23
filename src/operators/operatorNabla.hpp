
#ifndef __OPERATORNABLA_HPP__
#define __OPERATORNABLA_HPP__


#ifndef OPERATORNABLAX1D_TYPE_I
#define OPERATORNABLAX1D_TYPE_I(f, size, g) { for (long add=0; add<(size)-1; add++) g[add] = f[add+1] - f[add]; g[(size)-1] = 0; }
#endif
#ifndef OPERATORNABLAX_TYPE_I
#define OPERATORNABLAX_TYPE_I(f, size, offset, g) { for (long add=0; add<(size)-1; add++) g[add*offset] = f[add*offset] - f[add]; g[(size)-1] = 0; }
#endif

template <typename T> void operatorNablaX_type_I(T* f, long size, T* g)
{
	for (long x = 0; x < size1; x++)
		g[x] = f[x + 1] - f[x];
	g[size - 1] = (T)0;
}

template <typename T> void operatorNablaX_Type_I(T* f, int dimx, int dimy, int dimz, T* g)
{
	for (int z = 0; z < dimz; z++)
	{
		for (int y = 0; y < dimy; y++)
		{
			T* ff = &f[(long)dimx * dimy * z + (long)dimx * y];
			T* gg = &g[(long)dimx * dimy * z + (long)dimx * y];
			for (int x = 0; x < dimx; x++)
			{				
				OPERATORNABLAX1D_TYPE_I(ff, dimx , gg)
			}
		}
	}
}

/*
template <typename T> void operatorNablaY_Type_I(T* f, int dimx, int dimy, int dimz, T* g)
{
	for (int z = 0; z < dimz; z++)
	{
		for (int x = 0; x < dimx; x++)
		{
			T* ff = &f[(long)dimx * dimy * z + x];
			T* gg = &g[(long)dimx * dimy * z + x];
			for (int y = 0; y < dimx; y++)
			{
				OPERATORNABLAX_TYPE_I(ff, dimy, dimx, gg)
			}
		}
	}
}
*/

template <typename T> void operatorNablaY_Type_I(T* f, int dimx, int dimy, int dimz, T* g)
{
	for (int z = 0; z < dimz; z++)
	{
		for (int x = 0; x < dimx; x++)
		{
			
			for (int y = 0; y < dimx-1; y++)
			{
				long add0 = (long)dimx * dimy * z + (long)dimx * y + x;
				g[add0] = f[add0 + dimx] - f[add0];
			}
			long add0 = (long)dimx * dimy * z + (long)dimx * (dimy-1) + x;
			g[add0] = (T)0;
		}
	}
}

template <typename T> void operatorNablaZ_Type_I(T* f, int dimx, int dimy, int dimz, T* g)
{
	long offset = (long)dimx * dimy;
	for (int y = 0; y < dimy; y++)
	{
		for (int x = 0; x < dimx; x++)
		{
			T* ff = &f[(long)dimx* y + x];
			T* gg = &g[(long)dimx * y + x];
			for (int z = 0; z < dimz; z++)
			{
				OPERATORNABLAX_TYPE_I(ff, dimy, offset, gg)
			}
		}
	}
}


#endif