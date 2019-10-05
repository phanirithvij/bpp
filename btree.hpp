#ifndef BTREE
#define BTREE
class Btree
{
public:
    bool insert(int x);
    bool find(int x);
    int count(int x);
    void range(int x, int y);
    Btree();
    ~Btree();
};
#endif