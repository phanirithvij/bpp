#include "main.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

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
    while (getline(infile, line))
    {
        istringstream iss(line);
        if (!(iss >> b))
        {
            continue;
        }

        cout << b << "\n";
    }
    return 0;
}