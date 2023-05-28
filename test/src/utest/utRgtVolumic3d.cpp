
#include <stdio.h>
#include <vector>
#include <rgtVolumic.h>
#include <xt.h>
#include <debugIO.h>
#include <constraint.h>
#include <utRgtVolumic3d.h>

void utRgtVolumic3d()
{
	std::string pathxy = "D:\\JACK2\\DIR_PROJET\\UMC\\DATA\\3D\\UMCSmall\\DATA\\SEISMIC\\seismic3d.HR_NEAR_dipxy.xt";
	std::string pathxz = "D:\\JACK2\\DIR_PROJET\\UMC\\DATA\\3D\\UMCSmall\\DATA\\SEISMIC\\seismic3d.HR_NEAR_dipxz.xt";
	std::string seismicPath = "D:\\JACK2\\DIR_PROJET\\UMC\\DATA\\3D\\UMCSmall\\DATA\\SEISMIC\\seismic3d.HR_NEAR.xt";
	Xt xtxy = Xt(pathxy);
	Xt xtxz = Xt(pathxz);

	int x1 = 0;
	int x2 = 99;
	int y1 = 0;
	int y2 = 99;
	int z1 = 0;
	int z2 = 99;
	int dimx2 = x2 - x1 + 1;
	int dimy2 = y2 - y1 + 1;
	int dimz2 = z2 - z1 + 1;
	int size[3] = { dimx2, dimy2, dimz2 };
	long size0 = (long)dimx2 * dimy2 * dimz2;
	short* dipxy = new short[size0];
	short* seismic = new short[size0];
	short* dipxz = new short[size0];
	double* tau = new double[size0];
	double epsilon = 0.5;
	int nbIter = 3000;
	double leakyC = 70.0;

	xtxy.readSubVolume(x1, x2, y1, y2, z1, z2, dipxy);
	xtxz.readSubVolume(x1, x2, y1, y2, z1, z2, dipxz);
	Xt xtSeismic = Xt(seismicPath);
	xtSeismic.readSubVolume(x1, x2, y1, y2, z1, z2, seismic);

	Constraint* constr = new Constraint();
	std::vector<VOXEL> c0;
	VOXEL voxel;
	voxel.x = 60; voxel.y = 20;  voxel.z = 4;
	c0.push_back(voxel);
	voxel.x = 64; voxel.y = 90;  voxel.z = 4;
	c0.push_back(voxel);
	constr->addConstraint(c0);

	RgtVolumic* rgtVolumic = new RgtVolumic();
	rgtVolumic->setSize(size);
	rgtVolumic->setDipxy(dipxy);
	rgtVolumic->setDipxz(dipxz);
	rgtVolumic->setEpsilon(epsilon);
	rgtVolumic->setNbIter(nbIter);
	rgtVolumic->setTau(tau);
	rgtVolumic->setLeakyC(leakyC);
	rgtVolumic->setDipThreshold(2.0);
	rgtVolumic->setConstraint(constr);
	rgtVolumic->run();
	delete rgtVolumic;

	dataSave<short>("D:\\JACK2\\DEBUG\\seismic", (short*)seismic, size);
	dataSave<short>("D:\\JACK2\\DEBUG\\dipxy", (short*)dipxy, size);
	dataSave<double>("D:\\JACK2\\DEBUG\\tau", (double*)tau, size);
	/*
	int size[3] = { 100, 100, 100 };
	long size0 = (long)size[0] * size[1] * size[2];
	short* dipxy = new short[size0];
	short* dipxz = new short[size0];
	double* tau = new double[size0];
	double epsilon = 0.1;
	int nbIter = 100;
	double leakyC = 100.0;

	for (long i = 0; i < size0; i++) dipxy[i] = 1000;
	for (long i = 0; i < size0; i++) dipxz[i] = -500;

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
	*/
}

