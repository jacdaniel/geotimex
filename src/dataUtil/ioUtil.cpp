

#include <stdio.h>

#include <ioUtil.h>

void printWarning(std::string mess, std::string file, int line)
{
	fprintf(stderr, "%s in file %s [%d]\n", mess.c_str(), file.c_str(), line);
}

