

#include <conjugateGradientCallBack.h>

#ifndef __UTCONJUGATEGRADIENT__
#define __UTCONJUGATEGRADIENT__


template <typename T> class UtConjugateGradientCallBack : public ConjugateGradientCallBack<T>
{
public:
	UtConjugateGradientCallBack();
	virtual ~UtConjugateGradientCallBack();

	void callBack(void* in, void* out);
	void preconditionner(void *in, void *out);





};



#endif