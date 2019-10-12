#include "btree.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

BPtree::BPtree()
{
    // cout << "Node " << '\n';
    root = new Node();
    root->type = leaf;
}

void BPtree::insert(int x)
{
    insert(root, x);
}

void BPtree::insert(Node *curr, int x)
{
    if (curr->isleaf())
    {
        if (curr->insert(x))
        {
            // split
            curr->split(leaf);
        } else {
            
            cout << "else" << "\n";
            return;
        }
    }

    int i = 0;
    Node *next = new Node();
    cout << "val is " << curr->vals[i] << '\n';
    cout << "x is " << x << '\n';
    cout << "Node i" << '\n';
    while (x >= curr->vals[i])
    {
        cout << "i " << i << '\n';
        if (i + 1 < curr->vals.size())
        {
            i++;
        }
        else
        {
            cout << "iis " << i << '\n';
            break;
        }
    }
    next = curr->nodes[i];
    cout << "next is " << next << '\n';
}

int BPtree::count(int x)
{
    // cout << "count " << x << '\n';
    return 82190;
}

bool array_exists(Node *curr, int x)
{
    return (std::find(begin((*curr).vals), end((*curr).vals), x) != end((*curr).vals));
}

bool bfind(Node *curr, int x)
{
    if (curr->vals.size() == 0)
    {
        cout << "count = 0" << '\n';
        // node has no elts
        return false;
    }
    if (array_exists(curr, x))
    {
        cout << "found" << '\n';
        // found x in the node
        return true;
    }
    if (curr->isleaf())
    {
        return false;
    }
    int i = 0;
    // error
    Node *next = new Node();
    cout << "Node" << '\n';
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
};

bool BPtree::find(int x)
{
    return bfind(root, x);
}

void BPtree::range(int x, int y)
{
    cout << "range " << x << " " << y << '\n';
}

BPtree::~BPtree()
{
    // cout << "";
    cout << "Destroying BPtree" << '\n';
}

bool Node::isroot()
{
    return parent == nullptr;
}

bool Node::isleaf()
{
    cout << "leaf"
         << '\n';
    return type == leaf;
}

Node::Node(){};

void Node::split(NodeType type)
{
    if (type == leaf)
    {
        // leaf
        Node *newnode = new Node();
        newnode->type = leaf;
        this->next = newnode;

        int last = this->vals[this->vals.size() - 1];
        this->vals.pop_back();
        newnode->vals.push_back(last);

        last = this->vals[this->vals.size() - 1];
        this->vals.pop_back();
        newnode->vals.push_back(last);

        Node *parent = this->parent;
        int idx = parent->insert(newnode->vals[0]);
        parent->nodes.insert(parent->nodes.begin() + idx, newnode);
        if (parent->vals.size() <= 3)
        {
            // no overflow
            newnode->parent = parent;
            cout << this->parent;
            // this->nodes.insert()
            return;
        }
        else
        {
            // overflow
            parent->split(node);
        }
    }
    else
    {
        // non-leaf
        Node *newnode = new Node();

        int last = this->vals[this->vals.size() - 1];
        this->vals.pop_back();
        newnode->vals.push_back(last);

        Node *parent = this->parent;
        if (!parent->insert(newnode->vals[0]))
        {
            newnode->parent = parent;
            return;
        }
        else
        {
            // overflow
            parent->split(node);
        }
    }
}

bool Node::insert(int x, Node *newnode)
{
    this->vals.push_back(x);
    sort(this->vals.begin(), this->vals.end());
    return (this->vals.size() > 3);
}

int Node::insert(int x)
{
    this->vals.push_back(x);
    sort(this->vals.begin(), this->vals.end());
    for (int i = 0; i < this->vals.size(); i++)
        cout << this->vals[i] << " ";
    cout << '\n';
    // returns index
    return find(this->vals.begin(), this->vals.end(), x) - this->vals.begin();
}