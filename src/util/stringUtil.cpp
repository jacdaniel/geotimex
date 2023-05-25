

#include <stringUtil.h>


std::string stringExtension(std::string filename)
{
  return filename.substr(filename.find_last_of(".") + 1);
}