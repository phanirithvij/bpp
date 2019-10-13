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
    Node(NodeType type);
    bool isroot();
    bool isleaf();
    vector<int> vals;
    vector<Node *> nodes;
    NodeType type = node;
    Node *parent = nullptr;
    Node *next = nullptr;
    void print();
    void destroy();
    void print_self();
    void split(Node **root);
    bool insert(int val);
    int insert_index(int val);
};

class BPtree
{
public:
    Node *root;
    int count(int x);
    bool find(int x);
    void insert(int x);
    void insert(Node *curr, int x);
    void range(int x, int y);
    void print();
    void print_leaves();
    BPtree();
    ~BPtree();
};
#endif
