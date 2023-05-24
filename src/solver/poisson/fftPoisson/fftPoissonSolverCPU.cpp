
#include <stdio.h>

#include <memUtil.h>
#include <ioUtil.h>
#include <fftwUtil.h>

#include <debugIO.h>
#include <fftPoissonSolverCPU.h>

FFTPoissonSolverCPU::FFTPoissonSolverCPU()
{
}

FFTPoissonSolverCPU::~FFTPoissonSolverCPU()
{

}

FlagUtil::RET FFTPoissonSolverCPU::param1DInit()
{
	if (m_param == nullptr) return FlagUtil::RET::FAIL;
	m_param->m_pDir = fftw_plan_r2r_1d(m_param->m_size0, (double*)m_dataIn, (double*)m_param->m_freq, FFTW_REDFT10, FFTW_ESTIMATE);
	m_param->m_pInv = fftw_plan_r2r_1d(m_param->m_size0, (double*)m_param->m_freq, (double*)m_dataOut, FFTW_REDFT01, FFTW_ESTIMATE);
	m_param->m_norm = 2.0 * m_param->m_size0;
	if (m_param->m_pDir && m_param->m_pInv)
		return FlagUtil::RET::OK;
	else return FlagUtil::RET::FAIL;
}

FlagUtil::RET FFTPoissonSolverCPU::param2DInit()
{
	if (m_param == nullptr) return FlagUtil::RET::FAIL;
	m_param->m_pDir = fftw_plan_r2r_2d(m_size[1], m_size[0], (double*)m_dataIn, (double*)m_param->m_freq, FFTW_REDFT10, FFTW_REDFT10, FFTW_ESTIMATE);
	m_param->m_pInv = fftw_plan_r2r_2d(m_size[1], m_size[0], (double*)m_param->m_freq, (double*)m_dataOut, FFTW_REDFT01, FFTW_REDFT01,FFTW_ESTIMATE);
	m_param->m_norm = 4.0 * m_param->m_size0;
	if (m_param->m_pDir && m_param->m_pInv)
		return FlagUtil::RET::OK;
	else return FlagUtil::RET::FAIL;
}


FlagUtil::RET FFTPoissonSolverCPU::paramInit()
{
	if (m_param) return FlagUtil::RET::OK;
	m_param = new FFTPoissonSolverCPU::Param();
	m_param->m_dim = DataUtil::getDim(m_size);
	m_param->m_size0 = DataUtil::getSize0(m_size);

	m_param->m_fftLaplacian = new FFTLaplacian();
	m_param->m_fftLaplacian->setSize(m_size);
	m_param->m_fftLaplacian->init();

	m_param->m_freq = fftw_malloc(m_param->m_size0 * sizeof(double));

	FlagUtil::RET ret = FlagUtil::RET::OK;
	if (m_param->m_dim == DataUtil::DATA_DIM::DIM_1D)
	{
		ret = param1DInit();
	}
	else if (m_param->m_dim == DataUtil::DATA_DIM::DIM_2D)
	{
		ret = param2DInit();
	}

	return ret;
}

void FFTPoissonSolverCPU::run()
{
	double* in = (double*)m_dataIn;
	double* out = (double*)m_dataOut;

	if (paramInit() != FlagUtil::RET::OK) return;
	double* lap = (double*)m_param->m_fftLaplacian->getInvData();
	fftw_execute(m_param->m_pDir);
	double* freq = (double*)m_param->m_freq;
	for (long add = 0; add < m_param->m_size0; add++)	freq[add] *= lap[add];
	fftw_execute(m_param->m_pInv);
	for (int i = 0; i < m_param->m_size0; i++) out[i] /= m_param->m_norm;

	double *tmp = (double*)m_param->m_fftLaplacian->getData();
	dataSave<double>("d:\\JACK2\\DEBUG\\lp2d", tmp, m_size);
	// for (int i = 0; i < 60; i++)
	//	fprintf(stderr, "--> %d %f\n", i, tmp[i]);
	
	// for (int i = 0; i < m_param->m_size0; i++) fprintf(stderr, "%d %f\n", i, out[i]);
	// for (int i = 0; i < m_param->m_size0; i++) fprintf(stderr, "%d %f\n", i, 1.0/lap[i]);
}

/*
#include <fftPoissonCPU.h>


FFTPoissonCPU::FFTPoissonCPU()
{}

FFTPoissonCPU::~FFTPoissonCPU()
{
	paramRelease();
}




RETURN FFTPoissonCPU::paramInitDataAllocation()
{
	if (param == nullptr) return RETURN::FAIL;
	if (vars.dataIn == nullptr)
	{
		param->dataIn = fftw_alloc_real(param->size0 * sizeof(double));
		if (param->dataIn == nullptr)
		{
			PRINT_WARNING("error in allocation ")
				return  RETURN::FAIL;
		}
		param->pDataIn = param->dataIn;
	}
	else
	{
		param->pDataIn = vars.dataIn;
	}

	if (vars.dataFreq == nullptr)
	{
		param->dataFreq = (double*)fftw_alloc_real(param->size0 * sizeof(double));
		if (param->dataFreq == nullptr)
		{
			PRINT_WARNING("error in allocation ")
				return  RETURN::FAIL;
		}
		param->pDataFreq = param->dataFreq;
	}
	else
	{
		param->pDataFreq = vars.dataFreq;
	}

	if (vars.dataOut == nullptr)
	{
		param->dataOut = fftw_alloc_real(param->size0 * sizeof(double));
		if (param->dataOut == nullptr)
		{
			PRINT_WARNING("error in allocation ")
				return  RETURN::FAIL;
		}
		param->pDataOut = param->dataOut;
	}
	else
	{
		param->pDataOut = vars.dataOut;
	}

	return RETURN::SUCCESS;
}

RETURN FFTPoissonCPU::paramInit_1D()
{
	if (param == nullptr) return RETURN::FAIL;
	param->pDir = fftw_plan_r2r_1d(param->size0, (double*)param->pDataIn, (double*)param->pDataFreq, FFTW_REDFT10, FFTW_ESTIMATE);
	param->pInv = fftw_plan_r2r_1d(param->size0, (double*)param->pDataFreq, (double*)param->pDataOut, FFTW_REDFT01, FFTW_ESTIMATE);
	return RETURN::SUCCESS;
}

RETURN FFTPoissonCPU::paramInit()
{
	if (param != nullptr) return RETURN::SUCCESS;
	param = new PARAM();
	param->size0 = DataUtil::getSize0(vars.size);
	param->dim = DataUtil::getDim(vars.size);
	RETURN ret = paramInitDataAllocation();
	if (ret == RETURN::FAIL) return RETURN::FAIL;

	if (param->dim == DataUtil::DATA_DIM::DIM_1D)
	{
		ret = paramInit_1D();
		if (ret == RETURN::FAIL) return RETURN::FAIL;
	}
	else if (param->dim == DataUtil::DATA_DIM::DIM_2D)
	{
		ret = paramInit_2D();
		if (ret == RETURN::FAIL) return RETURN::FAIL;

	}
	else if (param->dim == DataUtil::DATA_DIM::DIM_3D)
	{
		ret = paramInit_3D();
		if (ret == RETURN::FAIL) return RETURN::FAIL;
	}
	else
	{
		return RETURN::FAIL;
	}
	return RETURN::SUCCESS;
}

RETURN FFTPoissonCPU::paramInit_2D()
{
	if (param == nullptr) return RETURN::FAIL;


	return RETURN::SUCCESS;
}

RETURN FFTPoissonCPU::paramInit_3D()
{
	if (param == nullptr) return RETURN::FAIL;


	return RETURN::SUCCESS;
}


RETURN FFTPoissonCPU::paramRelease()
{
	if (param == nullptr) return RETURN::SUCCESS;

	FFTW_FREE(param->dataIn)
	FFTW_FREE(param->dataFreq)
	FFTW_FREE(param->dataOut)
	FFTW_DESTROY_PLAN(param->pDir)
	FFTW_DESTROY_PLAN(param->pInv)
	DELETE(param)
	return RETURN::SUCCESS;
}
*/