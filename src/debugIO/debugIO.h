
#ifndef __DEBUGIO__
#define __DEBUGIO__

#include <debugIO.hpp>

class DebugIO
{
public:
	static void dataPrint(short *data, int dimx, int dimy = 1, int dimz = 1);
	static void dataPrint(double* data, int dimx, int dimy = 1, int dimz = 1);

	


};



#endif