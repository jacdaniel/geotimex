
#ifndef __SOLVERCALLBACK__
#define __SOLVERCALLBACK__

class SolverCallBack
{
public:
	SolverCallBack() { };
	virtual ~SolverCallBack() { };
	virtual void callBack(void* in, void* out) { };
	virtual void preconditionner(void* in, void* out) { };
};


#endif