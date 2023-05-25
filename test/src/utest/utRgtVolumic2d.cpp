
#include <utRgtVolumic2d.h>

#include <xt.h>
#include <stdio.h>
#include <rgtVolumic.h>

#include <debugIO.h>


void utRgtVolumic2d()
{
	/*
	int size[3] = { 100, 100, 1 };
	long size0 = (long)size[0] * size[1] * size[2];
	short* dipxy = new short[size0];
	short* dipxz = nullptr;
	double* tau = new double[size0];
	double epsilon = 1000.9;
	int nbIter = 100;
	double leakyC = 70.0;

	for (long i = 0; i < size0; i++) dipxy[i] = 1000;
	*/
	std::string path = "D:\\JACK2\\DIR_PROJET\\UMC\\DATA\\3D\\UMCSmall\\DATA\\SEISMIC\\seismic3d.HR_NEAR_dipxy.xt";
	std::string seismicPath = "D:\\JACK2\\DIR_PROJET\\UMC\\DATA\\3D\\UMCSmall\\DATA\\SEISMIC\\seismic3d.HR_NEAR.xt";
	Xt xt = Xt(path);


	int x1 = 0;
	int x2 = 399;
	int y1 = 0;
	int y2 = 1499;
	int z1 = 10;
	int z2 = 10;
	int dimx2 = x2 - x1 + 1;
	int dimy2 = y2 - y1 + 1;
	int dimz2 = z2 - z1 + 1;
	int size[3] = { dimx2, dimy2, dimz2 };
	long size0 = (long)dimx2 * dimy2 * dimz2;
	short* dipxy = new short[size0];
	short* seismic = new short[size0];
	short* dipxz = nullptr;
	double* tau = new double[size0];
	double epsilon = 0.1;
	int nbIter = 1500;
	double leakyC = 70.0;

	xt.readSubVolume(x1, x2, y1, y2, z1, z2, dipxy);
	Xt xtSeismic = Xt(seismicPath);
	xtSeismic.readSubVolume(x1, x2, y1, y2, z1, z2, seismic);

	RgtVolumic* rgtVolumic = new RgtVolumic();
	rgtVolumic->setSize(size);
	rgtVolumic->setDipxy(dipxy);
	rgtVolumic->setDipxz(dipxz);
	rgtVolumic->setEpsilon(epsilon);
	rgtVolumic->setNbIter(nbIter);
	rgtVolumic->setTau(tau);
	rgtVolumic->setLeakyC(leakyC);
	rgtVolumic->run();
	delete rgtVolumic;

	dataSave<short>("D:\\JACK2\\DEBUG\\seismic", (short*)seismic, size);
	dataSave<short>("D:\\JACK2\\DEBUG\\dipxy", (short*)dipxy, size);
	dataSave<double>("D:\\JACK2\\DEBUG\\tau", (double*)tau, size);	
}



