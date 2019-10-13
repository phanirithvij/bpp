#include "btree.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

BPtree::BPtree()
{
    cout << "init root" << '\n';
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
            curr->split(root);
        }
        else
        {
            cout << "insert successful"
                 << "\n";
            return;
        }
    }
    else
    {
        cout << "not a leaf"
             << "\n";
        int i = 0;
        Node *next = new Node(node);
        cout << "val is " << curr->vals[i] << '\n';
        cout << "x is " << x << '\n';
        cout << "nodes " << curr->nodes.size() << " " << curr->vals.size() << "\n";
        while (x >= curr->vals[i])
        {
            cout << "i " << i << '\n';
            if (i + 1 < curr->vals.size())
            {
                i += 1;
            }
            else
            {
                cout << "i is " << i << '\n';
                break;
            }
        }
        cout << curr->nodes.size() << '\n';
        // error
        next = curr->nodes[i];
        insert(next, x);
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
        // cout << "count = 0" << '\n';
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
        // reached a leaf but haven't found it yet
        return false;
    }
    int i = 0;
    Node *next = new Node(node);
    // cout << "Node" << '\n';
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
    root->destroy();
}

void Node::destroy()
{
    cout << "Destroying node" << endl;
    for (int i = 0; i < this->nodes.size(); i++)
    {
        cout << "i" << i << '\n';
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

// Node constructor
Node::Node(NodeType type)
{
    this->type = type;
};

// splits the current node according to it's type
void Node::split(Node *root)
{
    if (type == leaf)
    {
        cout << "it's a leaf" << '\n';
        // leaf
        Node *newnode = new Node(leaf);
        this->next = newnode;

        int last = this->vals[this->vals.size() - 1];
        this->vals.pop_back();
        newnode->vals.push_back(last);

        last = this->vals[this->vals.size() - 1];
        this->vals.pop_back();
        newnode->vals.push_back(last);

        if (this->isroot())
        {
            cout << "splitting root"
                 << "\n";
            this->parent = new Node(node);
            this->parent->nodes.push_back(this);
            root = parent;
            cout << "new root" << '\n';
        }

        int idx = parent->insert_index(newnode->vals[0]);
        parent->vals.insert(parent->vals.begin() + idx, newnode->vals[0]);
        parent->nodes.insert(parent->nodes.begin() + idx + 1, newnode);
        newnode->parent = parent;
        if (parent->vals.size() <= 3)
        {
            // no overflow
            cout << "leaf split successful" << '\n';
            cout << root->vals.size() << " " << root->nodes.size() << "\n";
            // this->nodes.insert()
            return;
        }
        else
        {
            // overflow
            parent->split(root);
        }
    }
    else if (type == node)
    {
        // non-leaf
        Node *newnode = new Node(node);

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
            cout << "splitting root"
                 << "\n";
            parent = new Node(node);
            parent->nodes.push_back(this);
            root = parent;
            cout << "new root" << '\n';
        }

        // insert lastbut one value in parent
        int idx = parent->insert_index(lastb);
        parent->vals.insert(parent->vals.begin() + idx, lastb);
        parent->nodes.insert(parent->nodes.begin() + idx + 1, newnode);
        newnode->parent = parent;

        if (parent->vals.size() <= 3)
        {
            cout << "node split done"
                 << "\n";
            cout << "now parent has " << parent->nodes.size() << " pointers"
                 << "\n";
            return;
        }
        else
        {
            // overflow
            parent->split(root);
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
    return upper_bound(this->vals.begin(), this->vals.end(), x) - this->vals.begin();
    // this->vals.push_back(x);
    // sort(this->vals.begin(), this->vals.end());
    // cout << "sorted vals:";
    // for (int i = 0; i < this->vals.size(); i++)
    //     cout << this->vals[i] << " ";
    // cout << '\n';
    // // returns index
    // int retval = find(this->vals.begin(), this->vals.end(), x) - this->vals.begin();
    // cout << "find " << retval << '\n';
    // return retval;
}
