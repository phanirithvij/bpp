#ifndef MAIN_H
#define MAIN_H
#include <string>
#include "btree.hpp"

bool file_exists(const std::string &name);
bool array_exists(Node *curr, int x);

#endif