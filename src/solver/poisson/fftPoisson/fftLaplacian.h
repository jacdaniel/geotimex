
#ifndef __FFTLAPLACIAN__
#define __FFTLAPLACIAN__

#include <returnFlags.h>
#include <dataUtil.h>
#include <dataFormat.h>

class FFTLaplacian
{
private:
	class PARAM
	{
	public:
		void* laplacian = nullptr;
		void* invLaplacian = nullptr;
		long size0 = 0;
		DataUtil::DATA_DIM dim = DataUtil::DATA_DIM::DIM_1D;

	};

	class VARS
	{
		public:
		int size[3] = { 1, 1, 1 };
		double mu = 0.0;
		double lambda = 0.0;
		DATA_FORMAT m_dataFormat = DATA_FORMAT::FLOAT32;
	};
public:
	FFTLaplacian();
	virtual ~FFTLaplacian();
	void setSize(int dimx, int dimy, int dimz) { vars.size[0] = dimx; vars.size[1] = dimy; vars.size[2] = dimz; }
	void setSize(int* size) { for (int i = 0; i < 3; i++) vars.size[i] = size[i]; }

	void init();
	void* getData();
	

private:
	VARS vars;
	PARAM* param = nullptr;
	RETURN paramInit();
	RETURN paramRelease();
	RETURN paramInit1D();
	RETURN paramInit2D();
	RETURN paramInit3D();
	RETURN apply(void* data);
	template <typename T> RETURN apply0(T* data);
};




#endif