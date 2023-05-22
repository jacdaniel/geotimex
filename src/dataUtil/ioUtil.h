
#ifndef __IOUTIL__
#define __IOUTIL__

#include <string>

void printWarning(std::string mess, std::string file, int line);

#define PRINT_WARNING(mess) { printWarning(mess, __FILE__, __LINE__); }



#endif