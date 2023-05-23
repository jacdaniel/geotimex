

#include <conjugateGradientCallBack.h>
#include <conjugateGradient.h>
#include <conjugateGradient.hpp>
#include <utConjugateGradientCallBack.hpp>

/*

    66    78    91
		78    93   110
		91   110   133

		x = 4     6     8

		y = 1460 1750 2088

*/

void utConjugateGradient()
{
	long size = 3;

	double rhs[] = { 1460, 1750, 2088 };
	double x[] = { 0, 100, 0 };

	UtConjugateGradientCallBack<double>* cb = new UtConjugateGradientCallBack<double>();
	cb->setSize(size);

	ConjugateGradient<double>* cg = new ConjugateGradient<double>();
	cg->setSize(size);
	cg->setCallback(cb);
	cg->setNbiter(10);
	cg->setRhs(rhs);
	cg->setX(x);
	cg->run();

	fprintf(stderr, "%f %f %f\n", x[0], x[1], x[2]);
}