
#include <algorithm>
// #include <omp.h>


#include <debugIO.h>
#include <operatorNabla.h>
#include <operatorNablaT.h>
#include <solver.h>
#include <flagUtil.h>
#include <memUtil.h>

#include <dipManager.h>
#include <surfaceReconstruction.h>

SurfaceReconstruction::SurfaceReconstruction()
{

}

SurfaceReconstruction::~SurfaceReconstruction()
{
	paramRelease();
}


bool SurfaceReconstruction::paramInit()
{
	if (m_param) return true;
	if (!m_dipManager) return false;
	m_param = new SurfaceReconstruction::Param();
	m_param->size0 = (long)m_size[0] * m_size[1] * m_size[2];
	m_param->mapSize = (long)m_size[1] * m_size[2];
	m_param->size2d[0] = m_size[1];
	m_param->size2d[1] = m_size[2];
	m_param->size2d[2] = 1;
	if (m_dipManager->getDipxy())
	{
		m_param->imgDipxy = new double[m_param->mapSize];
		m_param->dtauy = new double[m_param->mapSize];
		m_param->resy = new double[m_param->mapSize];
		m_param->divy = new double[m_param->mapSize];
	}
	if (m_dipManager->getDipxz())
	{
		m_param->imgDipxz = new double[m_param->mapSize];
		m_param->dtauz = new double[m_param->mapSize];
		m_param->resz = new double[m_param->mapSize];
		m_param->divz = new double[m_param->mapSize];
	}
	if (m_dipManager->getDipxy() || m_dipManager->getDipxz())
		m_param->imgValid = new char[m_param->mapSize];

	m_param->deltaTau = new double[m_param->mapSize];

	m_dipManager->setImgDipxy(m_param->imgDipxy);
	m_dipManager->setImgDipxz(m_param->imgDipxz);
	m_dipManager->setImgValid(m_param->imgValid);

	m_param->solver = new Solver();
	m_param->solver->setType(SOLVER_TYPE::POISSON);
	m_param->solver->setProcessing(FlagUtil::PROCESSING::CPU);
	m_param->solver->setSize(m_param->size2d);
	m_param->solver->setDataOut(m_param->deltaTau);

	return true;
}


bool SurfaceReconstruction::paramRelease()
{
	if (!m_param) return true;
	if (m_param->imgDipxy) { delete[] m_param->imgDipxy; m_param->imgDipxy = nullptr;  }
	DELETE_ARRAY(m_param->imgDipxy)
	DELETE_ARRAY(m_param->dtauy)
	DELETE_ARRAY(m_param->resy)
	DELETE_ARRAY(m_param->divy)
	DELETE_ARRAY(m_param->imgDipxz)
	DELETE_ARRAY(m_param->dtauz)
	DELETE_ARRAY(m_param->resz)
	DELETE_ARRAY(m_param->divz)
	DELETE_ARRAY(m_param->imgValid)
	DELETE_ARRAY(m_param->deltaTau)
	DELETE(m_param)
	return true;
}

bool SurfaceReconstruction::centerTau(void* _tau, long size, int x0, long addSeed)
{
	double* tau = (double*)_tau;
	if (!tau) return false;
	double xx = tau[addSeed];
	for (long add = 0; add < size; add++) tau[add] -= xx;
	for (long add = 0; add < size; add++) tau[add] += x0;
	return true;
}

bool SurfaceReconstruction::surfaceThreshold(void* _tau, long size, int xmin, int xmax)
{
	double* tau = (double*)_tau;
	if (!tau) return false;
	for (long add = 0; add < size; add++) tau[add] = std::min(std::max((double)xmin, tau[add]), (double)xmax);
	return true;
}

void SurfaceReconstruction::run()
{
	if (!paramInit())
	{
		paramRelease();
		return;
	}

	bool cont = true;
	m_iter = 0;
	double* tau = (double*)m_tau;
	double* dtauy = (double*)m_param->dtauy;
	double* dtauz = (double*)m_param->dtauz;
	double* resy = (double*)m_param->resy;
	double* resz = (double*)m_param->resz;
	double* imgDipxy = (double*)m_param->imgDipxy;
	double* imgDipxz = (double*)m_param->imgDipxz;
	double* divy = (double*)m_param->divy;
	double* divz = (double*)m_param->divz;
	double* deltaTau = (double*)m_param->deltaTau;
	long addSeed = (long)m_size[1] * m_zseed + m_yseed;
	char* valid = (char*)m_param->imgValid;

	for (long add = 0; add < m_param->mapSize; add++)
		((double*)m_tau)[add] = (double)m_xseed;
	long mod = m_nbIter / 10;

	while (cont)
	{
		if (m_iter % mod == 0)
		{
			fprintf(stderr, "surface reconstruction: %d / %d\n", m_iter, m_nbIter);
		}

		m_dipManager->run(m_tau);
		if (m_size[1] > 1 && m_param->imgDipxy)
		{
			OperatorNabla::NablaX(tau, m_param->size2d, dtauy);
			for (int i = 0; i < m_param->mapSize; i++) resy[i] = ( dtauy[i] - imgDipxy[i] ) * (double)valid[i];
			OperatorNablaT::NablaTX(resy, m_param->size2d, divy);
		}

		if (m_size[2] > 1 && m_param->imgDipxz)
		{
			OperatorNabla::NablaY(tau, m_param->size2d, dtauz);
			for (int i = 0; i < m_param->mapSize; i++) resz[i] = (dtauz[i] - imgDipxz[i])*(double)valid[i];
			OperatorNablaT::NablaTY(resz, m_param->size2d, divz);
		}
	
		// todo
		for (int i = 0; i < m_param->mapSize; i++) divz[i] += divy[i];
		

		m_param->solver->setDataIn(divz);
		m_param->solver->run();

		for (long i = 0; i < m_param->mapSize; i++)
			tau[i] += deltaTau[i];
		centerTau((void*)tau, m_param->mapSize, m_xseed, addSeed);
		
		m_iter++;;
		if (m_iter >= m_nbIter) cont = false;
	}
	surfaceThreshold(tau, m_param->mapSize, 0, m_size[0] - 1);
	// dataSave<double>("d:\\JACK2\\DEBUG\\tau", tau, m_param->size2d);
}

