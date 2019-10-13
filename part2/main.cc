#include "main.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include "hashing.hpp"
using namespace std;

unsigned long func(unsigned long value, const int &key)
{
    return (key & ((1 << (value + 1)) - 1));
}

int main(int argv, char **args)
{
    if (argv != 2)
    {
        cout << "Usage: " << args[0] << " <filename>"
             << "\n";
        return -1;
    }
    string filename = args[1];
    if (!file_exists(filename))
    {
        cout << "File " << filename << " doesn't exist"
             << "\n";
        return -1;
    }

    // file exists
    ifstream infile(filename);
    string line;
    int b;
    Hash hashe(1024 * 20, func);

    while (getline(infile, line))
    {
        istringstream iss(line);
        if (!(iss >> b))
        {
            continue;
        }

        if (!hashe.find(b))
        {
            cout << b << '\n';
            hashe.insert(b);
        }
    }
    return 0;
}