
#ifndef __CONJUGATEGRADIENTCALLBACK__
#define __CONJUGATEGRADIENTCALLBACK__


template <typename T> class ConjugateGradientCallBack
{
public:
	virtual void callBack(void* in, void* out)  = 0;
	virtual void preconditionner(void* in, void* out) = 0;
	void setSize(long size0) { m_size0 = size0; }
	void setSize3d(int* size) { for (int i = 0; i < 3; i++) m_size[i] = size[i]; }
	virtual double 	getCrit(T* data) { return 0.0; }

	// virtual void updateDataCallBack(void* data, int* size) = 0;
	// virtual void fonctionnelle(void* in, int iter_) = 0;

	// virtual void IterDisplay(void* xin) = 0;
	// virtual void setIter(int val) { m_iter = val; }
	// virtual void setIterMax(int val) { m_iterMax = val; }

	// void setX(void* val) { m_x = (T*)val; }
	// void setP(T* val) { m_P = val; }

protected:	
	long m_size0 = 0;
	int m_size[3] = { 1,1,1 };
};

#endif