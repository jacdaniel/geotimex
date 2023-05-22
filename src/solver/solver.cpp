

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
	}

	return FlagUtil::RET::OK;
}
