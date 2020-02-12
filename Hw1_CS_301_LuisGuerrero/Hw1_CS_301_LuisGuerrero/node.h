#pragma once
#include <string>

template<typename T>
struct node
{
	T& data;
	node<T>* next;

	node(T&);
	node(T&, node<T>*);
	virtual ~node() = default;
};

template <typename T>
node<T>::node(T& d) : data(d), next(nullptr)
{

}

template <typename T>
node<T>::node(T& d, node<T>* n) : data(d), next(n)
{

}
