#ifndef HASHS_HPP
#define HASHS_HPP
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#define BlockPair pair<Block *, Block *>

using namespace std;
typedef unsigned long ul;

class Block
{
	int capacity;
	std::vector<int> data;
	Block *next;

public:
	Block(int capacity);
	bool find(int &key);
	bool insert(int &key);
	bool empty();
	ul getHash(function<ul(int &)> hashFunc);
	BlockPair split(function<ul(int &)> hashFunc);
};

class Hash
{
	int capacity;
	std::vector<Block *> blocks;
	int current, currentHash;
	function<ul(ul, int &)> hashFunc;

public:
	Hash(ul capacity, function<ul(ul, int &)> hashFunc);
	void insert(int &key);
	bool find(int &key);
};
#endif //HASHS_HPP