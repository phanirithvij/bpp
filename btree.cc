#include "btree.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

Btree::Btree()
{
    root.isroot = true;
}

void Btree::insert(int x)
{
    cout << "inserting " << x << endl;
}

int Btree::count(int x)
{
    cout << "count " << x << endl;
    return 82190;
}

bool array_exists(Node *curr, int x)
{
    return (std::find(begin((*curr).vals), end((*curr).vals), x) != end((*curr).vals));
}

bool traverse(int x, int i, Node *curr)
{
    if (x == curr->vals[i])
    {
        // found the node
        return true;
    }
    else if (curr->vals[i] < x)
    {
        curr = curr->nodes[i];
    }
    else
    {
        curr = curr->nodes[i + 1];
    }
    return false;
}

bool bfind(Node *curr, int x)
{
    int count = curr->count;
    if (count == 0)
    {
        // node has no elts
        return false;
    }
    for (int i = 0; i < count; i++)
    {
        if (traverse(x, i, curr))
            return true;
        bfind(curr, x);
    }

    return false;
};

bool Btree::find(int x)
{
    return bfind(&root, x);
}

void Btree::range(int x, int y)
{
    cout << "range " << x << " " << y << endl;
}

Btree::~Btree()
{
    cout << "";
    // cout << "Destroying Btree" << endl;
}
