
#include <xt.h>


Xt::Xt()
{

}

Xt::Xt(std::string filename)
{
	m_pFile = fopen((char*)filename.c_str(), "rb");
	if (m_pFile == nullptr) { m_valid = false; return; }
	m_valid = true;
  headerRead();
}

Xt::~Xt()
{

}

#ifndef SAWP
#define SWAP(_a_, _b_, _temp_) { \
	_temp_ = _b_; \
	_b_ = _a_; \
	_a_ = _temp_; }
#endif 

void Xt::endianSwap(void* _data, long size, int length)
{
  long i, j;
  unsigned char temp, * data = (unsigned char*)_data;

  for (i = 0; i < size; i++)
    for (j = 0; j < length / 2; j++)
      SWAP(data[i * length + j], data[i * length + (length - 1 - j)], temp)
}

bool Xt::headerRead()
{
  if (!m_pFile) return false;
  fseek((FILE*)m_pFile, 4, SEEK_SET);
  fread((void*)&m_dimx, sizeof(int), 1, m_pFile); endianSwap(&m_dimx, 1, sizeof(int));
  fread((void*)&m_dimy, sizeof(int), 1, m_pFile); endianSwap(&m_dimy, 1, sizeof(int));
  fread((void*)&m_dimz, sizeof(int), 1, m_pFile); endianSwap(&m_dimz, 1, sizeof(int));
  fseek((FILE*)m_pFile, 32, SEEK_SET);
  fread((void*)&m_format, sizeof(int), 1, m_pFile); endianSwap(&m_format, 1, sizeof(int));
  fread((void*)&m_sizeof, sizeof(int), 1, m_pFile); endianSwap(&m_sizeof, 1, sizeof(int));
  fseek((FILE*)m_pFile, 72, SEEK_SET);
  fread((void*)&m_offset, sizeof(int), 1, m_pFile); endianSwap(&m_offset, 1, sizeof(int));
  // fprintf(stderr, "offset :%d\n", this->offset);
  return true;
}

bool Xt::recordsRead(long offset, long nbre, void* data)
{
  size_t off = (size_t)m_offset + (size_t)offset * m_dimx * 2;
  fseek((FILE*)m_pFile, off, SEEK_SET);
  fread(data, sizeof(short), (size_t)m_dimx * nbre, (FILE*)m_pFile);
  endianSwap(data, (long)m_dimx*nbre, sizeof(short));
	return true;
}

bool Xt::noSwapRecordsRead(long offset, long nbre, void* data)
{
  size_t off = (size_t)m_offset + (size_t)offset * m_dimx * 2;
  fseek((FILE*)m_pFile, off, SEEK_SET);
  fread(data, sizeof(short), (size_t)m_dimx * nbre, (FILE*)m_pFile);
  return true;
}

bool Xt::readSubVolume(int x1, int x2, int y1, int y2, int z1, int z2, void *data)
{
  int dimx = x2 - x1 + 1;
  int dimy = y2 - y1 + 1;
  int dimz = z2 - z1 + 1;
  short* data2 = new short[(size_t)m_dimx * dimy];
  if (data2 == nullptr) return false;
  for (int z = 0; z < dimz; z++)
  {
    noSwapRecordsRead((long)(z + z1) * m_dimy + y1, dimy, data2);
    for (int y = 0; y < dimy; y++)
    {
      for (int x = 0; x < dimx; x++)
      {
        ((short*)data)[(long)dimx * dimy * z + (long)dimx * y + x] = ((short*)data2)[(long)m_dimx * y + (x + x1)];
      }
    }
  }
  delete[] data2;
  endianSwap(data, (long)dimx*dimy*dimz, sizeof(short));
  return true;
}