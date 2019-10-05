#include <iostream>
#include "main.hpp"

using namespace std;

int main(int argv, char **args)
{
    if (argv != 2)
    {
        cout << "Usage: " << args[0] << " <filename>" << endl;
        exit(-1);
    }
    string filename = args[1];
    cout << "filename is " << filename << endl;
    cout << "File exists " << file_exists(filename) << endl;
    return 0;
}
