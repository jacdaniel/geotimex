

#include <test.h>
#include <testLaplacian1D.h>
#include <testReconstruction1d.h>
#include <testReconstruction2d.h>
#include <utConjugateGradient.h>
#include <utGradientDescent.h>
#include <utSurfaceReconstruction.h>
#include <utRgtVolumic3d.h>
#include <utRgtVolumic2d.h>
#include <utXt.h>

int test(int argc, char** argv)
{

	// testLaplacian1D();
	// testReconstruction1d();
	// testReconstruction2d();
	// utConjugateGradient();
	// utGradientDescent();
	// utSurfaceReconstruction();
	utRgtVolumic3d();
	// utRgtVolumic2d();
	//	utXt();
	return 1;
}