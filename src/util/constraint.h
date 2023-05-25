
#ifndef __CONSTRAINT__
#define __CONSTRAINT__

#include <vector>
#include <voxel.h>

typedef struct _CONSTRAINT
{
	std::vector<VOXEL> voxels;
	short vmean = 0;
}CONSTRAINT;


#endif