
#include <debugIO.hpp>
#include <xt.h>
#include <utXt.h>

void utXt()
{
	std::string path = "D:\\JACK2\\DIR_PROJET\\UMC\\DATA\\3D\\UMCSmall\\DATA\\SEISMIC\\seismic3d.HR_NEAR_dipxy.xt";
	Xt xt = Xt(path);
	int dimx = xt.dimx();
	int dimy = xt.dimy();
	int dimz = xt.dimz();
	bool valid = xt.isValid();
	int format = xt.format();
	int headerSize = xt.headerSize();
	fprintf(stderr, "xt: %s [%d]\nformat: %d\nheader size: %d\ndimx: %d\ndimy: %d\ndimz: %d\n", path.c_str(), (int)valid, format, headerSize, dimx, dimy, dimz);

	long size = (long)dimx * dimy;
	short* data = new short[size];
	xt.recordsRead(0, dimy, (void*)data);
	for (int i = 0; i < 10; i++)
		fprintf(stderr, "--> %d %d\n", i, data[i]);

	dataSave<short>("d:\\JACK2\\DEBUG\\seismic", data, dimx, dimy, 1);


	int x1 = 20;
	int x2 = 300;
	int y1 = 100;
	int y2 = 1000;
	int z1 = 10;
	int z2 = 100;
	int dimx2 = x2 - x1 + 1;
	int dimy2 = y2 - y1 + 1;
	int dimz2 = z2 - z1 + 1;
	long size2 = (long)dimx2 * dimy2 * dimz2;
	short* data2 = new short[size2];
	xt.readSubVolume(x1, x2, y1, y2, z1, z2, data2);


	dataSave<short>("d:\\JACK2\\DEBUG\\seismic", data, dimx, dimy, 1);
	dataSave<short>("d:\\JACK2\\DEBUG\\seismic2", data2, dimx2, dimy2, dimz2);


}