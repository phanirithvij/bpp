#include "main.hpp"

#ifdef _WIN32
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
bool file_exists(const std::string &name)
{
	return std::experimental::filesystem::exists(name);
}
#else
#include <sys/stat.h>
#include <unistd.h>
bool file_exists(const std::string &name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}
#endif
