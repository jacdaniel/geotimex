
#include <memUtil.h>

#include <leakyIntegration.h>
#include <rgtVolumicConjugateGradientCallBack.hpp>
#include <conjugateGradient.hpp>
#include <dataThreshold.hpp>
#include <rgtVolumic.h>

#include <debugIO.h>

RgtVolumic::RgtVolumic()
{

}

RgtVolumic::~RgtVolumic()
{

}

bool RgtVolumic::paramInit()
{
	if (m_param) return true;
	m_param = new RgtVolumic::Param();
	m_param->size0 = (long)m_size[0] * m_size[1] * m_size[2];

	m_param->rhs = new double[m_param->size0];
	// m_param->tau = new double[m_param->size0];

	if (m_leakyC > 0.0)
	{
		m_param->leakyIntegration = new LeakyIntegration<double>();
		m_param->leakyIntegration->setSize(m_size);
		m_param->leakyIntegration->setC(m_leakyC);
	}
	return true;
}

bool RgtVolumic::paramRelease()
{

	DELETE(m_param)
	return false;
}


void RgtVolumic::run()
{
	if (!paramInit())
	{
		paramRelease();
		return;
	}

	if ( m_dipThreshold >= 0.0 )
	{
	 short dipThreshold = (short)(m_dipThreshold * 1000.0);
	 dataThreshold<short>((short*)m_dipxy, m_param->size0, dipThreshold);
	 dataThreshold<short>((short*)m_dipxz, m_param->size0, dipThreshold);
	}

	RgtVolumicConjugateGradientCallBack<double>* callback = new RgtVolumicConjugateGradientCallBack<double>();
	callback->setSize3d(m_size);
	callback->setSize(m_param->size0);
	callback->setDipxy(m_dipxy);
	callback->setDipxz(m_dipxz);
	callback->setConstraint(m_constraint);

	callback->getRhs((double*)m_param->rhs);
	callback->getTauInit((double*)m_tau);
	callback->tauToS((double*)m_tau);
	callback->setLeakyIntegrator(m_param->leakyIntegration);
	callback->setEpsilon(m_epsilon);

	ConjugateGradient<double> *cg = new ConjugateGradient<double>();
	cg->setSize3d(m_size);
	cg->setSize(m_param->size0);
	cg->setCallback(callback);
	cg->setRhs((double*)m_param->rhs);
	cg->setX((double*)m_tau);
	cg->setNbiter(m_nbIter);
	cg->run();
	callback->sToTau((double*)m_tau);
	delete callback;
	delete cg;
}

