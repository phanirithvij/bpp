#include "main.h"

#ifdef _WIN32
#include <experimental/filesystem>
bool file_exists(std::string& fn)
{
    return std::experimental::filesystem::exists(fn);
}
#else
#include <sys/stat.h>
#include <unistd.h>
bool file_exists (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}
#endif
