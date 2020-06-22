#pragma once
#include <iostream>
#include <cstdio>

#include <string>
#include <unordered_map>

struct slist_node
{
	slist_node* prev;
	slist_node* next;
	slist_node* rand;
	std::string data;

	slist_node();
	slist_node(const std::string& data);
	slist_node(const slist_node& obj) = delete;
	slist_node(slist_node&& obj) = delete;

	slist_node& operator = (const slist_node& obj) = delete;
	slist_node& operator = (slist_node&& obj) = delete;
};

class slist
{
private:
	slist_node* _begin;
	slist_node* _end;
	size_t _size;

public:
	slist();
	slist(const slist& obj) = delete;
	slist(slist&& obj) = delete;
	~slist();

	slist& operator = (const slist& obj) = delete;
	slist& operator = (slist&& obj) = delete;

	void push_back(const std::string& data);
	void push_front(const std::string& data);
	void set_rand(const unsigned int node_index, const unsigned int point_to_index); // bruh...

	void serialize(FILE* file);
	void deserialize(FILE* file);

	friend std::ostream& operator << (std::ostream& os, const slist& obj);
};