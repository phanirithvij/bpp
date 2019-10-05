#include <iostream>
#include "main.hpp"
#include <fstream>
using namespace std;

int main(int argv, char **args)
{
    if (argv != 2)
    {
        cout << "Usage: " << args[0] << " <filename>" << endl;
        return -1;
    }
    string filename = args[1];
    if (!file_exists(filename))
    {
        cout << "File " << filename << " doesn't exist" << endl;
        return -1;
    }

    // file exists
    // ifstream infile(filename);
    // infile.close();

    Btree b = Btree();

    return 0;
}
