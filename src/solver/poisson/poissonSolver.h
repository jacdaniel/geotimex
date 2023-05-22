
#ifndef __POISSONSOLVER__
#define __POISSONSOLVER__

#include <flagUtil.h>
#include <solverUtil.h>

class FFTPoissonSolver;

class PoissonSolver
{
private:
	class Param
	{
	public:
		FFTPoissonSolver* m_fftPoissonSolver = nullptr;
	};

public:
	PoissonSolver();
	virtual ~PoissonSolver();
	void setMethode(SOLVER_METHODE methode) { m_methode = methode; }
	void setProcessing(FlagUtil::PROCESSING processing) { m_processing = processing; }
	void setSize(int* size) { m_size[0] = size[0]; m_size[1] = size[1]; m_size[2] = size[2]; }
	void setDataIn(void* data) { m_dataIn = data; }
	void setDataOut(void* data) { m_dataOut = data; }
	void run();

private:
	void* m_dataIn = nullptr;
	void* m_dataOut = nullptr;

private:
	SOLVER_METHODE m_methode = SOLVER_METHODE::FFT;
	FlagUtil::PROCESSING m_processing = FlagUtil::PROCESSING::CPU;
	int m_size[3] = { 1, 1, 1 };
	PoissonSolver::Param* m_param = nullptr;
	FlagUtil::RET paramInit();


};



#endif