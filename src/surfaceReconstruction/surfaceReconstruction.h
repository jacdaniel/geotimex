
#ifndef __SurfaceReconstruction__
#define __SURFACERECONSTRUCTION__

class DipManager;
class Solver;

class SurfaceReconstruction
{
private:
	class Param
	{
	public:
		long size0 = 0;
		long mapSize = 0;
		int size2d[3] = { 1,1,1 };
		void* imgDipxy = nullptr;
		void* imgDipxz = nullptr;
		void* imgValid = nullptr;
		void* dtauy = nullptr;
		void* dtauz = nullptr;
		void* resy = nullptr;
		void* resz = nullptr;
		void* divy = nullptr;
		void* divz = nullptr;
		void* deltaTau = nullptr;
		Solver* solver = nullptr;
	};
public:
	SurfaceReconstruction();
	virtual ~SurfaceReconstruction();
	void setDipManager(DipManager* data) { m_dipManager = data; }
	void setSeed(int xseed, int yseed) { m_xseed = xseed; m_yseed = yseed; m_zseed = 0; }
	void setSeed(int xseed, int yseed, int zseed) { m_xseed = xseed; m_yseed = yseed; m_zseed = zseed; }
	void setTau(void* data) { m_tau = data; }
	void setSize(int* size) { for (int i = 0; i < 3; i++)m_size[i] = size[i]; }
	void setSize(int dimx, int dimy) { m_size[0] = dimx; m_size[1] = dimy; m_size[2] = 1; }
	void setSize(int dimx, int dimy, int dimz) { m_size[0] = dimx; m_size[1] = dimy; m_size[2] = dimz; }
	void setNbIter(int n) { m_nbIter = n; }
	void run();

private:
	DipManager* m_dipManager = nullptr;
	int m_xseed = 0;
	int m_yseed = 0;
	int m_zseed = 0;
	void* m_tau = nullptr;
	int m_size[3] = { 1, 1, 1 };
	int m_nbIter = 20;
	int m_iter = 0;
	SurfaceReconstruction::Param* m_param = nullptr;
	bool paramInit();
	bool paramRelease();
	bool centerTau(void* _tau, long size, int x0, long addSeed);
	bool surfaceThreshold(void* _tau, long size, int xmin, int xmax);

};



#endif