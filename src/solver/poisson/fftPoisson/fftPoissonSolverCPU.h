
#ifndef __FFTPOISSONSOLVERCPU__
#define __FFTPOISSONSOLVERCPU__

#include <fftw3.h>

#include <flagUtil.h>
#include <fftLaplacian.h>
#include <dataUtil.h>

class FFTLaplacian;

class FFTPoissonSolverCPU
{
private:
	class Param
	{
	public:
		FFTLaplacian* m_fftLaplacian = nullptr;
		DataUtil::DATA_DIM m_dim = DataUtil::DATA_DIM::DIM_1D;
		fftw_plan m_pDir, m_pInv;
	};

public:
	FFTPoissonSolverCPU();
	virtual ~FFTPoissonSolverCPU();
	void setSize(int* size) { m_size[0] = size[0]; m_size[1] = size[1]; m_size[2] = size[2]; }

private:
	FFTPoissonSolverCPU::Param* m_param = nullptr;
	int m_size[3] = { 1, 1, 1 };
	FlagUtil::RET paramInit();
};


#endif
