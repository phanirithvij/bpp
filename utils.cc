#include <experimental/filesystem>
#include "main.h"

bool file_exists(std::string fn)
{
    return std::experimental::filesystem::exists(fn);
}
