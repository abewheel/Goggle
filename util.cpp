#include <cctype>
#include <algorithm>
#include "util.h"

std::string convToLower(std::string src) 
{
  std::transform(src.begin(), src.end(), src.begin(), ::tolower);
  return src;
}

