
#ifndef __DATAUTIL__
#define __DATAUTIL__


class DataUtil
{
public:
	enum class DATA_DIM { DIM_1D, DIM_2D, DIM_3D, DIM_UNDEFINED };

	static DATA_DIM getDim(int* size);
	static long getSize0(int* size);

};


#endif