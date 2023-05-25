

#ifndef __DATATHRESHOLD_HPP__
#define __DATATHRESHOLD_HPP__

#include <algorithm>

template <typename T> void dataThreshold(T* data, size_t size, T val)
{
	for (size_t add = 0; add < size; add++)
	{
		data[add] = std::min(data[add], val);
		data[add] = std::max(data[add], (T)(-val));
	}
}


#endif