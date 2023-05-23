#ifndef __OPERATORNABLAT_HPP__
#define __OPERATORNABLAT_HPP__



#ifndef OPERATORNABLATX1D_TYPE_I
#define OPERATORNABLATX1D_TYPE_I(f, size, g) { g[0] = -f[0]; for (long add=1; add<(size)-1; add++) g[add] = f[add-1] - f[add]; g[(size)-1] = f[(size)-2]; }
#endif
#ifndef OPERATORNABLATX_TYPE_I
#define OPERATORNABLATX_TYPE_I(f, size, offset, g)  { g[0] = -f[0]; for (long add=1; add<(size)-1; add++) g[add] = f[add-offset] - f[add]; g[(size)-1] = f[(size)-2*offset]; }
#endif

template <typename T> void operatorNablaTX_type_I(T* f, long size, T* g)
{
	for (long x = 0; x < size1; x++)
		g[x] = f[x - 1] - f[x];
	g[size - 1] = (T)0;
}

template <typename T> void operatorNablaTX_Type_I(T* f, int dimx, int dimy, int dimz, T* g)
{
	for (int z = 0; z < dimz; z++)
	{
		for (int y = 0; y < dimy; y++)
		{
			T* ff = &f[(long)dimx * dimy * z + (long)dimx * y];
			T* gg = &g[(long)dimx * dimy * z + (long)dimx * y];
			for (int x = 0; x < dimx; x++)
			{
				OPERATORNABLATX1D_TYPE_I(ff, dimx, gg)
			}
		}
	}
}

/*
template <typename T> void operatorNablaTY_Type_I(T* f, int dimx, int dimy, int dimz, T* g)
{
	for (int z = 0; z < dimz; z++)
	{
		for (int x = 0; x < dimx; x++)
		{
			T* ff = &f[(long)dimx * dimy * z + x];
			T* gg = &g[(long)dimx * dimy * z + x];
			for (int y = 0; y < dimy; y++)
			{
				OPERATORNABLATX_TYPE_I(ff, dimy, dimx, gg)
			}
		}
	}
}
*/

template <typename T> void operatorNablaTY_Type_I(T* f, int dimx, int dimy, int dimz, T* g)
{
	for (int z = 0; z < dimz; z++)
	{
		for (int x = 0; x < dimx; x++)
		{
			long add0 = (long)dimx * dimy * z + x;
			g[add0] = -f[add0];
			for (int y = 1; y < dimy-1; y++)
			{
				add0 = (long)dimx * dimy * z + (long)dimx*y + x;
				g[add0] = f[add0 + dimx] - f[add0];
			}
			add0 = (long)dimx * dimy * z + (long)dimx * (dimy-1) + x;
			g[add0] = f[add0 - dimx];
		}
	}
}

template <typename T> void operatorNablaTZ_Type_I(T* f, int dimx, int dimy, int dimz, T* g)
{
	long offset = (long)dimx * dimy;
	for (int y = 0; y < dimy; z++)
	{
		for (int x = 0; x < dimx; x++)
		{
			T* ff = &f[(long)dimx * y + x];
			T* gg = &g[(long)dimx * y + x];
			for (int z = 0; z < dimz; z++)
			{
				OPERATORNABLATX_TYPE_I(ff, dimy, offset, gg)
			}
		}
	}
}


#endif