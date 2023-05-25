

#ifndef __RGTVOLUMICCONJUGATEGRADIENTCALLBACK__
#define __RGTVOLUMICCONJUGATEGRADIENTCALLBACK__

#include <conjugateGradientCallBack.h>

template <typename T> class LeakyIntegration;



template <typename T> class RgtVolumicConjugateGradientCallBack : public ConjugateGradientCallBack<T>
{
public:
	RgtVolumicConjugateGradientCallBack();
	virtual ~RgtVolumicConjugateGradientCallBack();

	void callBack(void* in, void* out);
	void preconditionner(void* in, void* out);

	void setDipxy(void* data) { m_dipxy = data; }
	void setDipxz(void* data) { m_dipxz = data; }
	void getRhs(T* data);
	void getTauInit(T* data);
	void tauToS(T* data);
	void sToTau(T* data);
	void setEpsilon(double epsilon) { m_epsilon = epsilon; m_epsilon2 = m_epsilon * m_epsilon; }
	void setLeakyIntegrator(LeakyIntegration<T>* data) { m_leakyIntegrator = data; }
	double getCrit(T *data);

private:
	void* m_dipxy = nullptr;
	void* m_dipxz = nullptr;
	double m_epsilon = 0.1;
	double m_epsilon2 = m_epsilon * m_epsilon;
	double m_dipFactor = 1000.0f;
	double m_invDipFactor = 0.001f;
	double m_dipFactor2 = m_dipFactor * m_dipFactor;
	double m_invDipFactor2 = m_invDipFactor * m_invDipFactor;
	T rhsValue(int x, int y, int z);
	T opDirect(T* data, int x, int y, int z);
	LeakyIntegration<T>* m_leakyIntegrator = nullptr;
	double critVal(T* data, int x, int y, int z);

};



#endif