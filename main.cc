#include <iostream>
#include "main.hpp"
#include <fstream>
#include <sstream>
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
    ifstream infile(filename);
    string line;
    bool c_exists = false;
    string a;
    int b, c;
    Btree bt = Btree();
    while (getline(infile, line))
    {
        istringstream iss(line);
        if (iss >> a >> b)
            (iss >> c);
        else
        {
            continue;
        }

        // two args
        if (a == "INSERT")
        {
            bt.insert(b);
        }
        else if (a == "COUNT")
        {
            bt.count(b);
        }
        else if (a == "FIND")
        {
            if (bt.find(b)){
                // cou
            }
        }
        else
            bt.range(b, c);
    }

    return 0;
}
