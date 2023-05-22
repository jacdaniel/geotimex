
#include <iostream>

#include <debugIO.h>
#include <operatorNabla.h>
#include <operatorNablaT.h>
#include <solver.h>
#include <flagUtil.h>
#include <testReconstruction1d.h>


void testReconstruction1d()
{
	std::cout << __FUNCTION__ << std::endl;
	int size[] = { 101, 1, 1 };
	long size0 = (long)size[0] * size[1] * size[2];

	Solver* solver = new Solver();
	solver->setType(SOLVER_TYPE::POISSON);
	solver->setProcessing(FlagUtil::PROCESSING::CPU);
	solver->setSize(size);

	double* dipx = new double[size0];
	double* tau = new double[size0];
	double* dtau = new double[size0];
	double* res = new double[size0];
	double* div = new double[size0];

	int xseed = 50;
	int yseed = 150;

	for (int i = 0; i < size0; i++) tau[i] = xseed;
	for (int i = 0; i < size0; i++) dipx[i] = .1;
	OperatorNabla::NablaX(tau, size, dtau);
	for (int i = 0; i < size0; i++) res[i] = dtau[i] - dipx[i];
	OperatorNablaT::NablaTX(res, size, div);

	for (int i = 0; i < 5; i++) fprintf(stderr, "%d - %f %f\n", i, res[i], div[i]);
	for (int i = size0-5; i < size0; i++) fprintf(stderr, "%d - %f %f\n", i, res[i], div[i]);
	dataSave<double>("d:\\JACK2\\DEBUG\\res", res, size);




	delete[] dipx;
}