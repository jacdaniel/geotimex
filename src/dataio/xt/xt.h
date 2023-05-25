
#ifndef __XT__
#define __XT__

#include <string>
#include <stdio.h>

class Xt
{
public:
	Xt();
	Xt(std::string filename);
	virtual ~Xt();
	int dimx() { return m_dimx; }
	int dimy() { return m_dimy; }
	int dimz() { return m_dimz; }
	bool recordsRead(long offset, long nbre, void* data);
	bool readSubVolume(int x1, int x2, int y1, int y2, int z1, int z2, void *data);
	bool isValid() { return m_valid; }
	int format() { return m_format; }
	int headerSize() { return m_offset;  }



private:
	int m_dimx = 0;
	int m_dimy = 0;
	int m_dimz = 0;
	bool m_valid = false;
	// long m_headerSize = 5120;
	int m_format = 0;
	int m_sizeof = 0;
	int m_offset = 0;
	FILE* m_pFile = nullptr;
	bool headerRead();
	void endianSwap(void* _data, long size, int length);
	bool noSwapRecordsRead(long offset, long nbre, void* data);


};



#endif