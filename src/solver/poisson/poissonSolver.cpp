
#include <fftPoissonSolver.h>
#include <poissonSolver.h>


PoissonSolver::PoissonSolver()
{

}


PoissonSolver::~PoissonSolver()
{

}

FlagUtil::RET PoissonSolver::paramInit()
{
	if (m_param) return FlagUtil::RET::OK;
	m_param = new PoissonSolver::Param();
	if ( m_methode == SOLVER_METHODE::FFT )
	{
		m_param->m_fftPoissonSolver = new FFTPoissonSolver();
	}

	return FlagUtil::RET::OK;
}