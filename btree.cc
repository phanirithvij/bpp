#include "btree.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

BPtree::BPtree()
{
    // cout << "Node " << endl;
    root = new Node();
    root->isleaf = true;
}

void BPtree::insert(int x)
{
    insert(root, x);
}

void BPtree::insert(Node *curr, int x)
{
    if (curr->isleaf)
    {
        if (curr->insert(x))
        {
            // split
            curr->split(leaf);
        }
    }

    int i = 0;
    Node *next = new Node();
    cout << "Node i" << endl;
    while (x > curr->vals[i])
    {
        if (i + 1 < curr->vals.size())
        {
            i++;
        }
        else
        {
            break;
        }
    }
    next = curr->nodes[i];
}

int BPtree::count(int x)
{
    // cout << "count " << x << endl;
    return 82190;
}

bool array_exists(Node *curr, int x)
{
    return (std::find(begin((*curr).vals), end((*curr).vals), x) != end((*curr).vals));
}

bool bfind(Node *curr, int x)
{
    // cout << "Ass" << endl;
    if (curr->vals.size() == 0)
    {
        cout << "count = 0" << endl;
        // node has no elts
        return false;
    }
    if (array_exists(curr, x))
    {
        cout << "found" << endl;
        // found x in the node
        return true;
    }
    if (curr->isleaf)
    {
        return false;
    }
    int i = 0;
    // error
    Node *next = new Node();
    cout << "Node" << endl;
    while (x > curr->vals[i])
    {
        if (i + 1 < curr->vals.size())
        {
            i++;
        }
        else
        {
            break;
        }
    }
    next = curr->nodes[i];
    return bfind(next, x);
    // int index = distance(curr->vals, max_element(curr->vals, curr->vals + curr->count));
    // cout << "Index of max element: " << curr->vals[index] << endl;
};

bool BPtree::find(int x)
{
    cout << "find " << x << endl;
    return bfind(root, x);
    // return true;
}

void BPtree::range(int x, int y)
{
    cout << "range " << x << " " << y << endl;
}

BPtree::~BPtree()
{
    // cout << "";
    cout << "Destroying BPtree" << endl;
}

bool Node::isroot()
{
    return parent == nullptr;
}

void Node::split(NodeType type)
{
    if (type == leaf)
    {
        // leaf
        Node *newnode = new Node();
        newnode->isleaf = true;
        this->next = newnode;

        int last = this->vals[this->vals.size() - 1];
        this->vals.pop_back();
        newnode->vals.push_back(last);
        last = this->vals[this->vals.size() - 1];
        this->vals.pop_back();
        newnode->vals.push_back(last);

        Node *parent = this->parent;
        if (parent->vals.size() < 3)
        {
        }
    }
    else
    {
        // non-leaf
    }
}

bool Node::insert(int x)
{
    this->vals.push_back(x);
    sort(this->vals.begin(), this->vals.end());
    return (this->vals.size() > 3);
}
