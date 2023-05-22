
#include <fftPoissonSolverCPU.h>
#include <fftPoissonSolver.h>


FFTPoissonSolver::FFTPoissonSolver()
{

}

FFTPoissonSolver::~FFTPoissonSolver()
{

}

FlagUtil::RET FFTPoissonSolver::paramInit()
{
	if (m_param) return FlagUtil::RET::OK;
	m_param = new FFTPoissonSolver::Param();
	if (m_processing == FlagUtil::PROCESSING::CPU)
	{
		m_param->m_fftPoissonSolverCPU = new FFTPoissonSolverCPU();

	}
	return FlagUtil::RET::OK;
}