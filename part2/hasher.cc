#include "hashing.hpp"

Block::Block(int capacity)
{
    this->capacity = capacity;
    data = {};
    this->next = nullptr;
}

bool Block::Find(int &key)
{
    for (int pk : data)
    {
        if (pk == key)
            return true;
    }
    if (this->next != nullptr)
        return this->next->Find(key);
    return false;
}

bool Block::Insert(int &key)
{
    if (data.size() < this->capacity)
    {
        data.push_back(key);
        return false;
    }
    if (this->next == nullptr)
    {
        this->next = new Block(this->capacity);
    }
    this->next->Insert(key);
    return true;
}

bool Block::Empty()
{
    return data.empty();
}

ul Block::getHash(function<ul(int &)> hashFunc)
{
    return hashFunc(data[0]);
}

RT Block::Split(function<ul(int &)> hashFunc)
{
    RT splited;

    if (this->next != nullptr)
    {
        splited = this->next->Split(hashFunc);
        delete this->next;
        this->next = nullptr;
    }
    else
    {
        splited = RT(new Block(capacity), new Block(capacity));
    }

    for (int key : data)
    {
        ul hash = hashFunc(key);
        if (splited.first->Empty() && !splited.second->Empty())
        {
            if (hash == hashFunc(splited.second->data[0]))
                splited.second->Insert(key);
            else
                splited.first->Insert(key);
        }
        else if (splited.first->Empty() && splited.second->Empty())
        {
            splited.first->Insert(key);
        }
        else
        {
            if (hash != hashFunc(splited.first->data[0]))
                splited.second->Insert(key);
            else
                splited.first->Insert(key);
        }
    }
    return splited;
}

Hash::Hash(ul capacity, function<ul(ul, int &)> hashFunc)
{
    this->capacity = capacity;
    this->blocks.push_back(new Block(capacity));
    this->blocks.push_back(new Block(capacity));
    this->current = 0;
    this->currentHash = 0;
    this->hashFunc = hashFunc;
}

void Hash::Insert(int &key)
{
    ul hash = hashFunc(currentHash, key);
    if (hash < current)
        hash = hashFunc(currentHash + 1, key);
    bool overFlow = this->blocks[hash]->Insert(key);

    auto splitLambda = [this](int &key) {
        return hashFunc(currentHash + 1, key);
    };

    if (overFlow)
    {
        pair<Block *, Block *> splited = this->blocks[current]->Split(splitLambda);
        if ((!splited.first->Empty() && splited.first->getHash(splitLambda) != current) ||
            (!splited.second->Empty() && splited.second->getHash(splitLambda) == current))
            std::swap(splited.first, splited.second);

        delete this->blocks[current];
        this->blocks[current] = splited.first;
        this->blocks.push_back(splited.second);
        current++;

        if (this->blocks.size() == 2 * current)
        {
            current = 0;
            currentHash++;
        }
    }
}

bool Hash::Find(int &key)
{
    ul hash = hashFunc(currentHash, key);
    if (hash < current)
    {
        hash = hashFunc(currentHash + 1, key);
    }
    return blocks[hash]->Find(key);
}