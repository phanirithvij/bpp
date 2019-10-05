#ifndef BTREE
#define BTREE

class Node
{
public:
    int vals[3];
    Node *nodes[4];
    bool isroot = false;
    bool isleaf = false;
    Node *parent = nullptr;
    Node *next = nullptr;
    int count = 0;
};

class Btree
{
public:
    void insert(int x);
    bool find(int x);
    int count(int x);
    void range(int x, int y);
    Btree();
    ~Btree();

private:
    Node root;
};
#endif
