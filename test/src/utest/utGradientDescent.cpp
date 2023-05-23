
#include <stdio.h>

#include <gradientDescent.hpp>
#include <utGradientDescentCallBack.hpp>
#include <utGradientDescent.h>



void utGradientDescent()
{
	long size = 3;

	double rhs[] = { 1460, 1750, 2088 };
	double x[] = { 0, 0, 0 };

	UtGradientDescentCallBack<double>* cb = new UtGradientDescentCallBack<double>();
	cb->setSize(size);

	GradientDescent<double>* cg = new GradientDescent<double>();
	cg->setSize(size);
	cg->setCallback(cb);
	cg->setNbiter(1000000);
	cg->setX(x);
	cg->run();

	fprintf(stderr, "grad descent %f %f %f\n", x[0], x[1], x[2]);
}