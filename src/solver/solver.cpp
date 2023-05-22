

#include <poissonSolver.h>
#include <solver.h>

Solver::Solver()
{

}


Solver::~Solver()
{

}

FlagUtil::RET Solver::paramInit()
{
	if (m_param) return FlagUtil::RET::OK;
	m_param = new Solver::Param();
	if (m_type == SOLVER_TYPE::POISSON)
	{
		m_param->m_poissonSolver = new PoissonSolver();
		m_param->m_poissonSolver->setDataIn(m_dataIn);
		m_param->m_poissonSolver->setDataOut(m_dataOut);
		m_param->m_poissonSolver->setSize(m_size);
	}

	return FlagUtil::RET::OK;
}


void Solver::run()
{
	if (paramInit() != FlagUtil::RET::OK) return;
	if (m_param->m_poissonSolver)
	{
		m_param->m_poissonSolver->run();
	}
}
