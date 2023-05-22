
#include <iostream>
#include <fftLaplacian.h>
#include <debugIO.h>
#include <testLaplacian1d.h>

int testLaplacian1D()
{
	std::cout << "enter testLaplacian1D" << std::endl;

	FFTLaplacian* p = nullptr;
	p = new FFTLaplacian();
	int size[] = { 100, 1, 1 };
	p->setSize(size);
	p->init();
	double* data = (double*)p->getData();	
	DebugIO::dataPrint(data, size[0]);
	delete p;
	return 0;
}