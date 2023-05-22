
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
		long m_size0 = 0;
		fftw_plan m_pDir = nullptr, m_pInv = nullptr;
		void* m_freq = nullptr;
		double m_norm = 1.0;
	};

public:
	FFTPoissonSolverCPU();
	virtual ~FFTPoissonSolverCPU();
	void setSize(int* size) { m_size[0] = size[0]; m_size[1] = size[1]; m_size[2] = size[2]; }
	void setDataIn(void* data) { m_dataIn = data; }
	void setDataOut(void* data) { m_dataOut = data; }
	void run();

private:
	void* m_dataIn = nullptr;
	void* m_dataOut = nullptr;
	FFTPoissonSolverCPU::Param* m_param = nullptr;
	int m_size[3] = { 1, 1, 1 };
	FlagUtil::RET paramInit();
	FlagUtil::RET param1DInit();

};


#endif
