#ifndef BTREE
#define BTREE
#include <vector>
using namespace std;

enum NodeType{
    leaf, node
};

class Node
{
public:
    vector<int >vals;
    Node * nodes[4];
    Node *parent = nullptr;
    bool isroot();
    bool isleaf = false;
    Node *next = nullptr;
    void split(NodeType type);
    bool insert(int vals);
    Node();
};

class BPtree
{
public:
    void insert(Node *curr, int x);
    void insert(int x);
    bool find(int x);
    int count(int x);
    void range(int x, int y);
    BPtree();
    ~BPtree();

private:
    Node *root;
};
#endif
