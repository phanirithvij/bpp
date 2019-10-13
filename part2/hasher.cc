#include "hashing.hpp"

Block::Block(int capacity)
{
    this->capacity = capacity;
    data = {};
    this->next = nullptr;
}

bool Block::find(int &key)
{
    for (int pk : data)
    {
        if (pk == key)
            return true;
    }
    if (this->next != nullptr)
        return this->next->find(key);
    return false;
}

bool Block::insert(int &key)
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
    this->next->insert(key);
    return true;
}

bool Block::empty()
{
    return data.empty();
}

ul Block::getHash(function<ul(int &)> hashFunc)
{
    return hashFunc(data[0]);
}

BlockPair Block::split(function<ul(int &)> hashFunc)
{
    BlockPair spp;

    if (this->next != nullptr)
    {
        spp = this->next->split(hashFunc);
        delete this->next;
        this->next = nullptr;
    }
    else
    {
        spp = BlockPair(new Block(capacity), new Block(capacity));
    }

    for (auto key : data)
    {
        ul hash = hashFunc(key);
        if (spp.first->empty() && !spp.second->empty())
        {
            if (hash == hashFunc(spp.second->data[0]))
                spp.second->insert(key);
            else
                spp.first->insert(key);
        }
        else if (spp.first->empty() && spp.second->empty())
        {
            spp.first->insert(key);
        }
        else
        {
            if (hash != hashFunc(spp.first->data[0]))
                spp.second->insert(key);
            else
                spp.first->insert(key);
        }
    }
    return spp;
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

void Hash::insert(int &key)
{
    ul hash = hashFunc(currentHash, key);
    if (hash < current)
        hash = hashFunc(currentHash + 1, key);
    bool overFlow = this->blocks[hash]->insert(key);

    auto splitLambda = [this](int &key) {
        return hashFunc(currentHash + 1, key);
    };

    if (overFlow)
    {
        pair<Block *, Block *> spp = this->blocks[current]->split(splitLambda);
        if ((!spp.first->empty() && spp.first->getHash(splitLambda) != current) ||
            (!spp.second->empty() && spp.second->getHash(splitLambda) == current))
            std::swap(spp.first, spp.second);

        delete this->blocks[current];
        this->blocks[current] = spp.first;
        this->blocks.push_back(spp.second);
        current+=1;

        if (this->blocks.size() == 2 * current)
        {
            current = 0;
            currentHash++;
        }
    }
}

bool Hash::find(int &key)
{
    ul hash = hashFunc(currentHash, key);
    if (hash < current)
    {
        hash = hashFunc(currentHash + 1, key);
    }
    return blocks[hash]->find(key);
}