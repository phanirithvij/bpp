#ifndef HASHS_HPP
#define HASHS_HPP
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define RT pair<Block *, Block *>

#ifdef _WIN32
#include <functional>
#else
#include <function>
#endif


using namespace std;
typedef unsigned long ul;

class Block
{
	int capacity;
	std::vector<int> data;
	Block *next;

public:
	Block(int capacity);
	bool Find(int &key);
	bool Insert(int &key);
	bool Empty();
	ul getHash(function<ul(int &)> hashFunc);
	RT Split(function<ul(int &)> hashFunc);
};

class Hash
{
	int capacity;
	std::vector<Block *> blocks;
	int current, currentHash;
	function<ul(ul, int &)> hashFunc;

public:
	Hash(ul capacity, function<ul(ul, int &)> hashFunc);
	void Insert(int &key);
	bool Find(int &key);
};
#endif //HASHS_HPP