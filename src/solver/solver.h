
#ifndef __SOLVER__
#define __SOLVER__

#include <flagUtil.h>
#include <solverUtil.h>


class PoissonSolver;
class SolverCallBack;

// todo
// callback ?

class Solver
{	
private:
	class Param
	{
	public:
		PoissonSolver* m_poissonSolver = nullptr;
	};

public:
	Solver();
	virtual ~Solver();
	void setType(SOLVER_TYPE type) { m_type = type; }
	void setMethode(SOLVER_METHODE methode) { m_methode = methode; }
	void setProcessing(FlagUtil::PROCESSING processing) { m_processing = processing;  }
	void setSize(int* size) { m_size[0] = size[0]; m_size[1] = size[1]; m_size[2] = size[2]; }
	void setDataIn(void* data) { m_dataIn = data; }
	void setDataOut(void* data) { m_dataOut = data; }
	void setCallBack(SolverCallBack* callback) { m_callBack = callback;  }
	void run();

private:
	void* m_dataIn = nullptr;
	void* m_dataOut = nullptr;
	SOLVER_TYPE m_type = SOLVER_TYPE::POISSON;
	SOLVER_METHODE m_methode = SOLVER_METHODE::FFT;
	FlagUtil::PROCESSING m_processing = FlagUtil::PROCESSING::CPU;
	int m_size[3] = { 1, 1, 1 };
	Solver::Param* m_param = nullptr;
	FlagUtil::RET paramInit();
	SolverCallBack* m_callBack = nullptr;
};


#endif