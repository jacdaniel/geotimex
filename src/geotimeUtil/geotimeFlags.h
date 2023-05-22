
#ifndef __GEOTIMEFLAGS__
#define __GEOTIMEFLAGS__


class GeotimeFlags
{
public:
	enum SOLVER_METHODE { FOURIER, CONJUGATE_GRADIENT };
	enum PROCESSING_TYPE { CPU, GPU };
	enum POISSON_BOUND_CONDITIONS { NEUMANN, DIRICHLET };
	enum SOLVE_DIM { _1D, _2D, _3D, MULTI_1D, MULTI_2D };


};


#endif