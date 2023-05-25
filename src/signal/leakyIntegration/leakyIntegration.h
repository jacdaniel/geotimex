
#ifndef __LEAKYINTEGRATION__
#define __LEAKYINTEGRATION__


// void leakyIntegration(double *in, int *size, double c, double *out);

template <typename T> class LeakyIntegration
{
private:
	class PARAM
	{
	public:
		double** e = nullptr;
		double** t = nullptr;
		double** w = nullptr;
		T** v = nullptr;
		T** vr = nullptr;
		double sumT[3];
	};
public:
	LeakyIntegration();
	virtual ~LeakyIntegration();
	void setSize(int* size) { for (int i = 0; i < 3; i++) this->size[i] = size[i]; }
	void setC(double val) { c = val; }
	void run(T* in, T* out);


private:
	int size[3];
	double c = 26.0;
	int nbThreads = 30;
	char* mask2D = nullptr;
	PARAM* param = nullptr;
	int paramInit();
	int paramRelease();
	void integration(T* x, int size, double* e, double* t, double* w, T* y, T norm);
	void runX(T* in, T* out);
	void runY(T* in, T* out);
	void runZ(T* in, T* out);
	int m_preconditionnerSize = 5;
};


#endif
