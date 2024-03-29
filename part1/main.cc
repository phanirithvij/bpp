#include <iostream>
#include "main.hpp"
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
    bool c_exists = false;
    string a;
    int b, c;
    BPtree bt = BPtree();
    while (getline(infile, line))
    {
        // cout << line << "\n";
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
            // bt.root->print();
            // cout << "---\n";
        }
        else if (a == "COUNT")
        {
            cout << bt.count(b) << '\n';
        }
        else if (a == "FIND")
        {
            if (bt.find(b))
            {
                cout << "YES"
                     << "\n";
            }
            else
                cout << "NO"
                     << "\n";
        }
        else
        {
            bt.range(b, c);
        }
    }

    // bt.print_leaves();

    return 0;
}
