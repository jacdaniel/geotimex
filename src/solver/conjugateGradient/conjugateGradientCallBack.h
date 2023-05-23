
#ifndef __CONJUGATEGRADIENTCALLBACK__
#define __CONJUGATEGRADIENTCALLBACK__


template <typename T> class ConjugateGradientCallBack
{
public:
	virtual void callBack(void* in, void* out)  = 0;
	virtual void preconditionner(void* in, void* out) = 0;
	void setSize(long size0) { m_size0 = size0; }
	// virtual void updateDataCallBack(void* data, int* size) = 0;
	// virtual void fonctionnelle(void* in, int iter_) = 0;

	// virtual void IterDisplay(void* xin) = 0;
	// virtual void setIter(int val) { m_iter = val; }
	// virtual void setIterMax(int val) { m_iterMax = val; }

	// void setX(void* val) { m_x = (T*)val; }
	// void setP(T* val) { m_P = val; }

protected:	
	long m_size0 = 0;
};

#endif