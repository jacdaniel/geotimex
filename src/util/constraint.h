
#ifndef __CONSTRAINT__
#define __CONSTRAINT__

#include <vector>
#include <voxel.h>

class Constraint
{
public:
	Constraint();
	virtual ~Constraint();
	std::vector<std::vector<VOXEL>> m_voxels;
	short vmean = 0;
	size_t getNbre() { return m_voxels.size(); }
	size_t getNbre(long n) { if (n >= 0 && n < m_voxels.size()) return m_voxels[n].size(); else return -1; }
	std::vector<VOXEL> getConstraint(int n) { if (n >= 0 && n < m_voxels.size()) return m_voxels[n]; else return std::vector<VOXEL>();  }

	void addConstraint(std::vector<VOXEL>& constraint) { m_voxels.push_back(constraint); }
};


#endif