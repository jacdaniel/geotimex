
#ifndef __FFTPOISSONSOLVER__
#define __FFTPOISSONSOLVER__

#include <flagUtil.h>
#include <solverUtil.h>

class FFTPoissonSolverCPU;

class FFTPoissonSolver
{
private:
	class Param
	{
	public:
		FFTPoissonSolverCPU* m_fftPoissonSolverCPU = nullptr;
	};
public:
	FFTPoissonSolver();
	virtual ~FFTPoissonSolver();
	void setProcessing(FlagUtil::PROCESSING processing) { m_processing = processing; }
	void setSize(int* size) { m_size[0] = size[0]; m_size[1] = size[1]; m_size[2] = size[2]; }
	void setDataIn(void* data) { m_dataIn = data; }
	void setDataOut(void* data) { m_dataOut = data; }
	void run();

private:
	void* m_dataIn = nullptr;
	void* m_dataOut = nullptr;

private:
	FlagUtil::PROCESSING m_processing = FlagUtil::PROCESSING::CPU;
	int m_size[3] = { 1, 1, 1 };
	FFTPoissonSolver::Param* m_param = nullptr;
	FlagUtil::RET paramInit();

};



#endif