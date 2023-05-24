
#include <debugIO.h>

#include <dipManager.h>
#include <surfaceReconstruction.h>
#include <utSurfacereconstruction.h>

void utSurfaceReconstruction()
{
	int size[3] = { 100,101,102 };
	long size0 = (long)size[0] * size[1] * size[2];
	short* dipxy = new short[size0];
	short* dipxz = new short[size0];
	double* tau = new double[(long)size[1] * size[2]];
	for (long add = 0; add < size0; add++) dipxy[add] = 1000;
	for (long add = 0; add < size0; add++) dipxz[add] = 2000;
	int xseed = 50;
	int yseed = 50;
	int zseed = 50;


	DipManager* dipManager = new DipManager();
	dipManager->setSize(size);
	dipManager->setDipxy((void*)dipxy);
	dipManager->setDipxz((void*)dipxz);

	SurfaceReconstruction* surfaceReconstruction = new SurfaceReconstruction();
	surfaceReconstruction->setDipManager(dipManager);
	surfaceReconstruction->setSeed(xseed, yseed, zseed);
	surfaceReconstruction->setTau(tau);
	surfaceReconstruction->setSize(size);
	surfaceReconstruction->setNbIter(200);
	surfaceReconstruction->run();

	surfaceReconstruction->setSeed(70, yseed, zseed);
	surfaceReconstruction->run();
	dataSave<double>("d:\\JACK2\\DEBUG\\tau", tau, size[1], size[2], 1);

	delete dipManager;
	delete surfaceReconstruction;
}