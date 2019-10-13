#include "btree.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
// #include "assert.h"
#include <cassert>
using namespace std;

BPtree::BPtree()
{
    // cout << "init root" << '\n';
    root = new Node(leaf);
}

void BPtree::insert(int x)
{
    insert(root, x);
}

void BPtree::insert(Node *curr, int x)
{
    if (curr->isleaf())
    {
        if (!curr->insert(x))
        {
            // split
            // cout << "overflow" << '\n';
            curr->split(&root);
        }
        else
        {
            // cout << "insert successful"
            //      << "\n";
            return;
        }
    }
    else
    {
        // cout << "\nnot a leaf"
        //      << "\n";
        int i = 0;
        Node *next_node = new Node(node);
        // cout << "val is " << curr->vals[i] << '\n';
        // cout << "x is " << x << '\n';
        while (x > curr->vals[i])
        {
            // cout << x << ">" << curr->vals[i] << '\n';
            // cout << "i " << i << '\n';
            if (i + 1 <= curr->vals.size())
            {
                i += 1;
            }
            else
            {
                // cout << "i is " << i << '\n';
                break;
            }
        }
        // cout << "i2 " << i << '\n';
        // cout << "curr vals, nodes size " << curr->vals.size() << " " << curr->nodes.size() << '\n';
        // error
        // ignore assert
        // assert(i < curr->nodes.size());
        next_node = curr->nodes[i];
        // cout << "next_node is " << next_node << '\n';
        // cout << "i.e\n";
        next_node->parent = curr;
        // cout << "same parent? " << (next_node->parent == curr) << endl;
        // next_node->print_self();
        insert(next_node, x);
    }
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

// Finds if a given key exists in the tree
bool bfind(Node *curr, int x)
{
    if (curr->vals.size() == 0)
    {
        // cout << "empty node" << '\n';
        // node has no elts
        return false;
    }
    if (array_exists(curr, x))
    {
        // cout << "found" << '\n';
        // found x in the node
        return true;
    }
    if (curr->isleaf())
    {
        // reached a leaf but haven't found it yet
        return false;
    }
    int i = 0;
    Node *next = new Node(node);
    // cout << "Node" << '\n';
    while (x > curr->vals[i])
    {
        if (i + 1 <= curr->vals.size())
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

bool Node::isroot()
{
    return parent == nullptr;
}

bool Node::isleaf()
{
    // cout << "leaf"
    //      << '\n';
    return type == leaf;
}

// Node constructor
Node::Node(NodeType type)
{
    this->type = type;
};

// splits the current node according to it's type
void Node::split(Node **root)
{
    if (type == leaf)
    {
        // leaf
        auto newnode = new Node(leaf);
        this->next = newnode;

        int last = this->vals[this->vals.size() - 1];
        this->vals.pop_back();
        int lastb = this->vals[this->vals.size() - 1];
        this->vals.pop_back();

        // cout << "lastb, last " << lastb << ',' << last << '\n';

        newnode->vals.push_back(lastb);
        newnode->vals.push_back(last);

        if (this->isroot())
        {
            // cout << "splitting root"
            //      << "\n";
            // cout << "root split" << '\n';
            parent = new Node(node);
            parent->nodes.push_back(this);
            *root = parent;
            // cout << "root==parent " << (parent == (*root)) << '\n';
            // cout << "new root" << '\n';
        }
        // else
            // cout << "leaf split" << '\n';
        // (*root)->print();
        newnode->parent = parent;
        // cout << "vals " << newnode->vals[0] << "," << newnode->vals[1] << '\n';
        int idx = parent->insert_index(newnode->vals[0]);
        // cout << "idx " << idx << '\n';
        parent->vals.insert(parent->vals.begin() + idx, newnode->vals[0]);
        parent->nodes.insert(parent->nodes.begin() + idx + 1, newnode);
        if (parent->vals.size() <= 3)
        {
            // no overflow
            // cout << "leaf split successful" << '\n';
            // cout << (*root)->vals[0] << " " << (*root)->nodes.size() << "\n";
            return;
        }
        else
        {
            // overflow
            parent->split(&(*root));
        }
    }
    else if (type == node)
    {
        // non-leaf
        // cout << "non-leaf split started" << '\n';
        Node *newnode = new Node(node);
        // this->next = newnode;

        int last = this->vals[this->vals.size() - 1];
        this->vals.pop_back();
        newnode->vals.push_back(last);

        int lastb = this->vals[this->vals.size() - 1];
        this->vals.pop_back();

        Node *lastn = this->nodes[this->nodes.size() - 1];
        Node *lastnb = this->nodes[this->nodes.size() - 2];
        this->nodes.pop_back();
        this->nodes.pop_back();

        newnode->nodes.push_back(lastnb);
        newnode->nodes.push_back(lastn);

        if (this->parent == nullptr)
        {
            // cout << "splitting root"
            //      << "\n";
            parent = new Node(node);
            parent->nodes.push_back(this);
            *root = parent;
            // cout << "new root" << '\n';
        }

        // insert lastbut one value in parent
        int idx = parent->insert_index(lastb);
        parent->vals.insert(parent->vals.begin() + idx, lastb);
        parent->nodes.insert(parent->nodes.begin() + idx + 1, newnode);
        newnode->parent = parent;

        if (parent->vals.size() <= 3)
        {
            // cout << "node split done"
            //      << "\n";
            // cout << "now root has " << (*root)->vals.size() << " vals"
            //      << "\n";
            // root->print();
            return;
        }
        else
        {
            // overflow
            parent->split(&(*root));
        }
    }
}

// inserts node and returns false if an overflow
bool Node::insert(int x)
{
    this->vals.push_back(x);
    sort(this->vals.begin(), this->vals.end());
    return (this->vals.size() <= 3);
}

// returns index
int Node::insert_index(int x)
{
    int dx = lower_bound(vals.begin(), vals.end(), x) - vals.begin();
    // cout << "insert_index: vals ";
    // print_self();
    return dx;
}

void BPtree::print()
{
    root->print();
}

void Node::print()
{
    // cout << "node has " << nodes.size() << " pointers" << '\n';
    for (int i = 0; i < nodes.size(); i += 1)
    {
        nodes[i]->print();
    }
    if (type == leaf && !isroot())
    {
        cout << "l-";
    }
    else if (isroot())
    {
        cout << "r-";
    }
    print_self();
}

void BPtree::print_leaves(){
    auto curr = root;
    while (curr->nodes.size() != 0){
        curr = curr->nodes[0];
    }
    curr->print_self();
}

void Node::print_self()
{
    for (int i = 0; i < vals.size(); i += 1)
    {
        cout << vals[i] << " ";
    }
    cout << '\n';
}

BPtree::~BPtree()
{
    // cout << "";
    // cout << "Destroying BPtree" << '\n';
    root->destroy();
}

void Node::destroy()
{
    // cout << "Destroying node" << endl;
    for (int i = 0; i < this->nodes.size(); i++)
    {
        // cout << "i" << i << '\n';
        Node *nodex = new Node(node);
        nodex = this->nodes[i];
        nodex->destroy();
    }
    this->vals.clear();
    if (this->type == leaf)
    {
        delete (this);
        return;
    }
}