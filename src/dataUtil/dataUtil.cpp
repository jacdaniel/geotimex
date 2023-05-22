

#include <dataUtil.h>

DataUtil::DATA_DIM DataUtil::getDim(int* size)
{
	if (size == nullptr) return DataUtil::DATA_DIM::DIM_UNDEFINED;
	if (size[0] > 1 && size[1] == 1 && size[2] == 1) return DataUtil::DATA_DIM::DIM_1D;
	if (size[0] > 1 && size[1] > 1 && size[2] == 1) return DataUtil::DATA_DIM::DIM_2D;
	if (size[0] > 1 && size[1] > 1 && size[2] > 1) return DataUtil::DATA_DIM::DIM_3D;
	return DataUtil::DATA_DIM::DIM_UNDEFINED;
}


long DataUtil::getSize0(int* size)
{
	if (size == nullptr) return 0;
	return (long)size[0] * size[1] * size[2];
}