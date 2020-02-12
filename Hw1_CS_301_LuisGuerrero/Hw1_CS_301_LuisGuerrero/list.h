#pragma once
#include<string>

#include"node.h"

template <typename T>
class list
{
public:
	list();
	~list();

	bool isEmpty() const;
	int getCount() const;

	virtual node<T>* insert(T&, const int);
	virtual node<T>* insertFirst(T&);
	virtual node<T>* insertLast(T&);
	void removeNode(const int);
	void removeNodeByName(std::string&);
	T& getAvailable();
	bool checkAvailable();

	void printLinkedList();
	void printHolidays();

protected:
	int count;
	node<T>* head;

};

template <typename T>
list<T>::list() : count(0), head(nullptr)
{
}

template <typename T>
list<T>::~list()
{
}

template <typename T>
bool list<T>::isEmpty() const
{
	return count == 0;
}

template <typename T>
int list<T>::getCount() const
{
	return count;
}

template <typename T>
node<T>* list<T>::insert(T& names, const int position)
{
	if (position < 0 || position > count)
	{
		throw "error";
	}

	node<T>* returnNode;

	if (head == nullptr) //list is empty
	{
		head = new node<T>(names);

		returnNode = head;
	}
	else if (position == 0)//replacing head
	{
		node<T>* temp = head;
		head = new node<T>(names, temp);

		returnNode = head;
	}
	else
	{
		node<T>* currentNode = head;
		for (int i = 0; i < position - 1; i++)
		{
			currentNode = currentNode->next;
		}

		node<T>* temp = currentNode->next;
		currentNode->next = new node<T>(names, temp);

		returnNode = currentNode->next;
	}
	count++;

	return returnNode;
}

template <typename T>
node<T>* list<T>::insertFirst(T& name)
{
	return insert(name, 0);
}

template <typename T>
node<T>* list<T>::insertLast(T& name)
{
	return insert(name, count);
}

template <typename T>
void list<T>::removeNode(int position)
{
	if (position < 0 || position > count - 1)
	{
		throw "Error: Out of rage";
	}
	else if (head == nullptr)
	{
		throw "List is already empty";
	}

	if (position == 0)
	{
		node<T>* currentNode = head->next;
		delete head;

		head = currentNode;
	}
	else
	{
		node<T>* prevNode = nullptr;
		node<T>* currNode = head;
		for (int i = 0; i < position; i++)
		{
			prevNode = currNode;
			currNode = currNode->next;
		}
		prevNode->next = currNode->next;
		delete currNode;
	}
	count--;
	return;
}

template <typename T>
void list<T>::removeNodeByName(std::string& nameToDelete)
{
	node<T>* currentNode = head;

	for (int i = 0; i < count; i++)
	{
		if (currentNode->data == nameToDelete)
		{
			removeNode(i);
			return;
		}
		else
		{
			currentNode = currentNode->next;
		}
	}
}

template <typename T>
T& list<T>::getAvailable()
{
	node<T>* currentNode = head;
	std::string& temp = currentNode->data;

	while (currentNode->data == "0" || currentNode->next != nullptr)
	{
		currentNode = currentNode->next;
	}
	temp = currentNode->data;
	currentNode->data = "0";
	return temp;
}

template <typename T>
bool list<T>::checkAvailable()
{
	node<T>* tempNode = head;
	while (tempNode->data == "0"|| tempNode->next != nullptr)
	{
		tempNode = tempNode->next;
	}
	return true;
}

template <typename T>
void list<T>::printLinkedList()
{
	node<T>* currentNode;
	currentNode = head;

	while (currentNode->next != nullptr)
	{
		std::cout << currentNode->data << std::endl;
		currentNode = currentNode->next;
	}
}

template <typename T>
void list<T>::printHolidays()
{
	node<T>* currentNode = head;
	std::string space = " ";
	space.resize(20, ' ');
	while (currentNode->next != nullptr)
	{
		std::cout << space << currentNode->data << std::endl;
		currentNode = currentNode->next;
	}
}
