
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
		m_param->m_fftPoissonSolverCPU->setDataIn(m_dataIn);
		m_param->m_fftPoissonSolverCPU->setDataOut(m_dataOut);
		m_param->m_fftPoissonSolverCPU->setSize(m_size);
	}
	return FlagUtil::RET::OK;
}


void FFTPoissonSolver::run()
{
	if (paramInit() != FlagUtil::RET::OK) return;
	if (m_param->m_fftPoissonSolverCPU)
	{
		m_param->m_fftPoissonSolverCPU->run();
	}
}