

#ifndef __DIPMANAGER__
#define __DIPMANAGER__

class DipManager
{
public:
	DipManager();
	virtual ~DipManager();
	void setDipxy(void* data) { m_dipxy = data; }
	void setDipxz(void* data) { m_dipxz = data; }
	void setImgDipxy(void* data) { m_imgDipxy = data; }
	void setImgDipxz(void* data) { m_imgDipxz = data; }
	void setImgValid(void* data) { m_imgValid = data; }
	void setSize(int* size) { for (int i = 0; i < 3; i++) m_size[i] = size[i]; }
	void setSize(int dimx, int dimy, int dimz) { m_size[0] = dimx; m_size[1] = dimy; m_size[2] = dimz; }
	void* getDipxy() { return m_dipxy; }
	void* getDipxz() { return m_dipxz; }
	void run(void *_tau);

private:
	void* m_dipxy = nullptr;
	void* m_dipxz = nullptr;
	int m_decimy = 1;
	int m_decimz = 1;
	void* m_imgDipxy = nullptr;
	void* m_imgDipxz = nullptr;
	void* m_imgValid = nullptr;
	int m_size[3] = { 1, 1, 1 };
	int m_normShort = 1000;
	void dipExtract(void* _tau, void* _dip, void* _imgDip);
};

#endif