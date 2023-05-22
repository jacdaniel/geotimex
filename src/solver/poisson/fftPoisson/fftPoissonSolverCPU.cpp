
#include <stdio.h>

#include <memUtil.h>
#include <ioUtil.h>
#include <fftwUtil.h>

#include <fftPoissonSolverCPU.h>

FFTPoissonSolverCPU::FFTPoissonSolverCPU()
{
}

FFTPoissonSolverCPU::~FFTPoissonSolverCPU()
{

}

FlagUtil::RET FFTPoissonSolverCPU::paramInit()
{
	if (m_param) return FlagUtil::RET::OK;
	m_param = new FFTPoissonSolverCPU::Param();
	m_param->m_dim = DataUtil::getDim(m_size);

	m_param->m_fftLaplacian = new FFTLaplacian();
	m_param->m_fftLaplacian->setSize(m_size);
	// void init();

	return FlagUtil::RET::OK;
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