#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "list.h"
#include "node.h"


using namespace std;

void displayMenu();

int main()
{
	ifstream inFileN, inFileH;
	ofstream outFile;
	string inFileName, outFileName, names, customerName;
	string inFileHol, outFileHoli, holidayName, holidays;
	int userOption, userAgain = 0;

	outFile.open("Magic.txt");


	cout << "Enter the name of the magicians file you want to open: ";
	cin >> inFileName;
	cout << endl;

	inFileN.open(inFileName.c_str());

	if (!inFileN)
	{
		cout << "ERROR: File could not be opened..." << endl;

		return 0;

	}

	list<string> magicianList;

	while (getline(inFileN, names))
	{
		string temp = names;
		magicianList.insertFirst(names);
	}

	magicianList.printLinkedList();
	system("pause");

	cout << "Enter the name of the holidays file you want to open: ";
	cin >> inFileHol;
	cout << endl;

	inFileH.open(inFileHol.c_str());

	if (!inFileH)
	{
		cout << "ERROR: File could not be found or open..." << endl;

		return 0;
	}

	list<string> holidayList;

	while (getline(inFileH, holidays))
	{
		holidayList.insertLast(holidays);
	}


	inFileH.close();
	inFileN.close();

	list<list<string>> waitingList;
	list<list<string>> bookingHoliday;
	list<list<string>> bookingMagician;
	list<string> customer_holiday;
	list<string> magician_holiday;

	do
	{
		system("CLS");
		displayMenu();
		cin >> userOption;

		switch (userOption)
		{
		case 1:
			do
			{
				system("CLS");

				cout << "Please enter the name of the customer: ";
				getline(cin.ignore(), customerName);
				cout << endl;

				holidayList.printHolidays();
				cout << "Please enter the name of the holiday the customer wants: ";
				getline(cin, holidayName);
				cout << endl;

				if (magicianList.checkAvailable() == true)
				{
					string magician = magicianList.getAvailable();
					customerName.resize(20, ' ');
					magician.resize(20, ' ');

					cout << "CUSTOMER: " << customerName << "	MAGICIAN: " << magician << "HOLIDAY: " << holidayName << endl << endl;
					customer_holiday.insertFirst(customerName);
					customer_holiday.insertLast(holidayName);
					bookingHoliday.insertFirst(customer_holiday);

					magician_holiday.insertFirst(magician);
					magician_holiday.insertLast(holidayName);
					bookingMagician.insertFirst(magician_holiday);

					//outFile << "CUSTOMER: " << customerName << "MAGICIAN: " << magician << "HOLIDAY: " << holidayName << endl << endl;


					cout << "Would you like to schedule for another holiday? [1]YES [2]NO" << endl;
					cin >> userAgain;


				}
				else
				{
					cout << "There are no magicians available" << endl;
					cout << "You are currently on the waiting list..." << endl << endl;
					//waitingList.insertLast(customerName);
					//waitingList.insertLast(holidayName);


				}


			} while (userAgain == 1);
			break;
		case 2:
			system("CLS");

			cout << "Enter the name of the person you want to remove: ";
			getline(cin.ignore(), customerName);
			cout << endl;

			cout << "Enter the name of the holiday the magician was schedule: ";
			getline(cin.ignore(), holidayName);
			cout << endl;



			break;
		case 3:
			system("CLS");
			break;
		case 4:
			system("CLS");
			break;
		case 5:
			system("CLS");
			break;
		case 6:
			system("CLS");
			break;
		default:
			break;
		}
	} while (userOption != 6);


	system("pause");
	return 0;
}

void displayMenu()
{
	cout << "================ Main Menu ================" << endl << endl;
	cout << setw(29) << "[ 1 ] SCHEDULE " << endl;
	cout << setw(27) << "[ 2 ] CANCEL " << endl;
	cout << setw(40) << "[ 3 ] NEW MAGICIAN SIGNUP " << endl;
	cout << setw(37) << "[ 4 ] MAGICIAN DROPOUT " << endl;
	cout << setw(26) << "[ 5 ] STATUS" << endl;
	cout << setw(24) << "[ 6 ] QUIT" << endl << endl;

	cout << "Choose an option : ";
}