#pragma once
#include <string>


struct node
{
	std::string& data;
	node* next;

	node(std::string&);
	node(std::string&, node*);
	virtual ~node() = default;
};


node::node(std::string& d) : data(d), next(nullptr)
{

}


node::node(std::string& d, node* n) : data(d), next(n)
{

}
