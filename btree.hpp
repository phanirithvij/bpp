#ifndef BTREE
#define BTREE
#include <vector>
using namespace std;

enum NodeType
{
    leaf,
    node
};

class Node
{
public:
    vector<int> vals;
    vector<Node *> nodes;
    Node *parent = nullptr;
    bool isroot();
    bool isleaf();
    NodeType type = node;
    Node *next = nullptr;
    void split(Node *root);
    int insert_index(int val);
    bool insert(int val);
    Node(NodeType type);
    void destroy();
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
