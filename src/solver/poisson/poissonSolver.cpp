
#include <stdio.h>
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
		m_param->m_fftPoissonSolver->setDataIn(m_dataIn);
		m_param->m_fftPoissonSolver->setDataOut(m_dataOut);
		m_param->m_fftPoissonSolver->setSize(m_size);
	}

	return FlagUtil::RET::OK;
}

void PoissonSolver::run()
{
	if (paramInit() != FlagUtil::RET::OK) return;
	if (m_param->m_fftPoissonSolver)
	{
		m_param->m_fftPoissonSolver->run();
	}

}
