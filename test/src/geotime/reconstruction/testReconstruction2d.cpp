

#include <iostream>
#include <malloc.h>

#include <debugIO.h>
#include <operatorNabla.h>
#include <operatorNablaT.h>
#include <solver.h>
#include <flagUtil.h>

#include <testReconstruction2d.h>



void testReconstruction2d()
{
	std::cout << __FUNCTION__ << std::endl;
	int size[] = { 101, 102, 1 };
	long size0 = (long)size[0] * size[1] * size[2];

	/*
	double* dipx = new double[size0];
	double* tau = new double[size0];
	double* dtau = new double[size0];
	double* res = new double[size0];
	double* div = new double[size0];
	*/

	double* dipxy = (double*)calloc(size0, sizeof(double));
	double* dipxz = (double*)calloc(size0, sizeof(double));
	double* tau = (double*)calloc(size0, sizeof(double));
	double* dtauy = (double*)calloc(size0, sizeof(double));
	double* dtauz = (double*)calloc(size0, sizeof(double));
	double* resy = (double*)calloc(size0, sizeof(double));
	double* resz = (double*)calloc(size0, sizeof(double));
	double* divy = (double*)calloc(size0, sizeof(double));
	double* divz = (double*)calloc(size0, sizeof(double));

	int xseed = 50;
	int yseed = 50;
	int zseed = 50;

	for (int i = 0; i < size0; i++) tau[i] = xseed;
	for (int i = 0; i < size0; i++) dipxy[i] = .1;
	for (int i = 0; i < size0; i++) dipxz[i] = -.2;

	OperatorNabla::NablaX(tau, size, dtauy);
	OperatorNabla::NablaY(tau, size, dtauz);
	for (int i = 0; i < size0; i++) resy[i] = dtauy[i] - dipxy[i];
	for (int i = 0; i < size0; i++) resz[i] = dtauz[i] - dipxz[i];


	OperatorNablaT::NablaTX(resy, size, divy);
	OperatorNablaT::NablaTY(resz, size, divz);
	for (int i = 0; i < size0; i++) divz[i] += divy[i];

	dataSave<double>("d:\\JACK2\\DEBUG\\res", divz, size[0], size[1], 1);

	Solver* solver = new Solver();
	solver->setType(SOLVER_TYPE::POISSON);
	solver->setProcessing(FlagUtil::PROCESSING::CPU);
	solver->setSize(size);
	solver->setDataIn((void*)divz);
	solver->setDataOut((void*)tau);
	solver->run();

	dataSave<double>("d:\\JACK2\\DEBUG\\tau", tau, size[0], size[1], 1);


	// delete[] dipx;
	std::cout << __FUNCTION__ << std::endl;
}