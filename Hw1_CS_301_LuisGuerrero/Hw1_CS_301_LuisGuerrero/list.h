#pragma once
#include<string>
#include <fstream>
#include"node.h"

class list
{
public:
	list();
	~list();

	bool isEmpty() const;
	int getCount() const;

	node* insert(std::string&, const int);
	node* insertFirst(std::string&);
	node* insertLast(std::string&);
	void removeNode(const int);
	bool removeNodeByName(std::string&);
	void removeAllNodes();
	std::string getAvailable();
	std::string getHoliday(std::string);
	std::string& getData(const int);
	std::string& getFirstData();
	std::string getMagicianByHoliday(std::string);
	std::string getCustomerByMagician(std::string);
	std::string getHolidayByMagician(std::string);
	std::string getCustomerWaiting(std::string);
	bool checkAvailable();
	bool checkHolidayWaiting(std::string);

	void printLinkedList();
	void printListCus_Hol();
	void printToOutputFile(std::ofstream&);
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


void list::removeNode(const int position)
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


bool list::removeNodeByName(std::string& nameToDelete)
{
	node* currentNode = head;
	bool removed = false;
	for (int i = 0; i < count; i++)
	{
		if (currentNode->data == nameToDelete)
		{
			
			removeNode(i);
			removed = true;
			return true;
		}
		else
		{
			currentNode = currentNode->next;
		}
	}
	std::cout << "Data could not be found..." << std::endl;
}

void list::removeAllNodes()
{
	if (head == nullptr)
	{
		return;
	}
	else
	{
		node* currentNode = head;
		while (currentNode->next != nullptr)
		{
			node* previousNode = currentNode;
			currentNode = currentNode->next;
			delete previousNode;
		}
		delete currentNode;
	}
	count = 0; 
	head = nullptr;

	return;
}


std::string list::getAvailable()
{
	node* currentNode = head;
	std::string temp;

	while (currentNode->data == "0" && currentNode->next != nullptr)
	{
		currentNode = currentNode->next;
	}
	temp = currentNode->data;
	currentNode->data = "0";
	return temp;
}

std::string list::getHoliday(std::string holidayName)
{
	node* currNode = head;
	std::string returnHoliday = holidayName;

	for (int i = 0; i < count; i++)
	{
		if (currNode->data == holidayName)
		{
			return currNode->data;
		}
		else
		{
			currNode = currNode->next;
		}
	}
	return returnHoliday;
}


std::string& list::getData(const int pos)
{
	if (head == nullptr) //The list is empty
	{
		throw "List is empty";
	}

	if (pos < 0 || pos > count - 1)
	{
		throw "Index out of range.";
	}

	node* currentNode = head;
	for (int i = 0; i < pos; i++)
	{
		currentNode = currentNode->next;
	}

	return currentNode->data;
}


std::string& list::getFirstData()
{
	return getData(0);
}

std::string list::getMagicianByHoliday(std::string holiday)
{
	node* currNode = head;
	std::string magicianFound;
	while (currNode->next != nullptr)
	{
		if (currNode->data == holiday)
		{
			currNode = currNode->next;
			magicianFound = currNode->data;
			return magicianFound;
		}
		currNode = currNode->next;
	}
	return magicianFound;
}

std::string list::getCustomerByMagician(std::string magicianName)
{
	node* currNode = head;
	std::string customerFound = "Customer not found...";
	for (int i = 0; i < count; i++)
	{
		if (currNode->data == magicianName)
		{
			customerFound = getData(i - 2);
			return customerFound;
		}
		currNode = currNode->next;
	}
	return customerFound;
}

std::string list::getHolidayByMagician(std::string magicianName)
{
	node* currNode = head;
	std::string holidayFound = "Customer not found...";
	for (int i = 0; i < count; i++)
	{
		if (currNode->data == magicianName)
		{
			holidayFound = getData(i - 1);
			return holidayFound;
		}
		currNode = currNode->next;
	}
	return holidayFound;
}

std::string list::getCustomerWaiting(std::string holidayName)
{
	node* currNode = head;
	std::string customerName;
	while (currNode->next != nullptr)
	{
		if (currNode->data == holidayName)
		{
			currNode = currNode->next;
			customerName = currNode->data;
			return customerName;
		}
		currNode = currNode->next;
	}
	return customerName;
}


bool list::checkAvailable()
{
	node* tempNode = head;
	bool available = false;
	while (tempNode->data == "0")
	{
		if(tempNode->next != nullptr)
		{
			tempNode = tempNode->next;
		}
		else 
		{
			return available;
		}
	}
	available = true;
	return available;
}

bool list::checkHolidayWaiting( std::string holidayName)
{
	bool check = false;
	node* currNode = head;
	
	while (currNode->next != nullptr)
	{
		if (currNode->data == holidayName)
		{
			check = true;
			return check;
		}
		currNode = currNode->next;
	}
	return check;
}


void list::printLinkedList()
{
	node* currentNode = head;
	std::string space = " ";
	space.resize(20, ' ');
	for (int i = 0; i < count ; i++)
	{
		std::cout << space << currentNode->data << std::endl;
		currentNode = currentNode->next;
	}
}

void list::printListCus_Hol()
{
	node* currentNode = head;
	for (int i = 0; i < count / 3; i++)
	{
		std::string name = currentNode->data;
		name.resize(20, ' ');
		std::cout << "CUSTOMER: " << name;
		currentNode = currentNode->next;
		std::string holiday = currentNode->data;
		holiday.resize(20, ' ');
		std::cout << "HOLIDAY: " << holiday;
		currentNode = currentNode->next;
		std::string magician = currentNode->data;
		magician.resize(20, ' ');
		std::cout << "MAGICIAN: " << magician << std::endl;
		currentNode = currentNode->next;
	}
}

void list::printToOutputFile(std::ofstream& outputFile)
{
	node* currNode = head;
	for (int i = 0; i < count / 3; i++)
	{
		std::string name = currNode->data;
		name.resize(20, ' ');
		outputFile << "CUSTOMER: " << name;
		currNode = currNode->next;
		std::string holiday = currNode->data;
		holiday.resize(20, ' ');
		outputFile << "HOLIDAY: " << holiday;
		currNode = currNode->next;
		std::string magician = currNode->data;
		magician.resize(20, ' ');
		outputFile << "MAGICIAN: " << magician << std::endl;
		currNode = currNode->next;
	}
}
