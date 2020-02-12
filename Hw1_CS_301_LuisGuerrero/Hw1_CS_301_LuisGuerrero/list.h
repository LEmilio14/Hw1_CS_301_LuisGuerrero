#pragma once
#include<string>

#include"node.h"


class list
{
public:
	list();
	~list();

	bool isEmpty() const;
	int getCount() const;

	virtual node* insert(std::string&, const int);
	virtual node* insertFirst(std::string&);
	virtual node* insertLast(std::string&);
	void removeNode(const int);
	void removeNodeByName(std::string&);
	std::string& getAvailable();
	bool checkAvailable();

	void printLinkedList();
	void printHolidays();

protected:
	int count;
	node* head;

};


list::list() : count(0), head(nullptr)
{
}


list::~list()
{
}


bool list::isEmpty() const
{
	return count == 0;
}


int list::getCount() const
{
	return count;
}


node* list::insert(std::string& names, const int position)
{
	if (position < 0 || position > count)
	{
		throw "error";
	}

	node* returnNode;

	if (head == nullptr) //list is empty
	{ 
		head = new node(names);

		returnNode = head;
	}
	else if (position == 0)//replacing head
	{
		node* temp = head;
		head = new node(names, temp);

		returnNode = head;
	}
	else
	{
		node* currentNode = head;
		for (int i = 0; i < position - 1; i++)
		{
			currentNode = currentNode->next;
		}

		node* temp = currentNode->next;
		currentNode->next = new node(names, temp);

		returnNode = currentNode->next;
	}
	count++;

	return returnNode;
}


node* list::insertFirst(std::string& name)
{
	return insert(name, 0);
}


node* list::insertLast(std::string& name)
{
	return insert(name, count);
}


void list::removeNode(int position)
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
		node* currentNode = head->next;
		delete head;

		head = currentNode;
	}
	else
	{
		node* prevNode = nullptr;
		node* currNode = head;
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


void list::removeNodeByName(std::string& nameToDelete)
{
	node* currentNode = head;

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


std::string& list::getAvailable()
{
	node* currentNode = head;
	std::string& temp = currentNode->data;

	while (currentNode->data == "0" || currentNode->next != nullptr)
	{
		currentNode = currentNode->next;
	}
	temp = currentNode->data;
	currentNode->data = "0";
	return temp;
}


bool list::checkAvailable()
{
	node* tempNode = head;
	while (tempNode->data == "0"|| tempNode->next != nullptr)
	{
		tempNode = tempNode->next;
	}
	return true;
}


void list::printLinkedList()
{
	node* currentNode;
	currentNode = head;

	while (currentNode->next != nullptr)
	{
		std::cout << currentNode->data << std::endl;
		currentNode = currentNode->next;
	}
}


void list::printHolidays()
{
	node* currentNode = head;
	std::string space = " ";
	space.resize(20, ' ');
	while (currentNode->next != nullptr)
	{
		std::cout << space << currentNode->data << std::endl;
		currentNode = currentNode->next;
	}
}
