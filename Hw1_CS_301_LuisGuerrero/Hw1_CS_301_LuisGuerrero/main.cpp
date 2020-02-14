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
	ofstream outFile, scheduleFile;
	string inFileName, outFileName, name, customerName, magician, newMagician, dropOutMagician;
	string inFileHol, outFileHoli, holidayName, holidays, magicianRelocated, waitingCustomer;
	string redistCustomer, redistHoliday;
	int userOption, userAgain = 0;

	outFile.open("Magic1.txt");
	scheduleFile.open("Schedule.txt");

	cout << "Enter the name of the magicians file you want to open: ";
	cin >> inFileName;
	cout << endl;

	inFileN.open(inFileName.c_str());

	if (!inFileN)
	{
		cout << "ERROR: File could not be opened..." << endl;

		return 0;

	}

	list magicianList;

	while (getline(inFileN, name))
	{
		magicianList.insertLast(name);
	}

	cout << "Enter the name of the holidays file you want to open: ";
	cin >> inFileHol;
	cout << endl;

	inFileH.open(inFileHol.c_str());

	if (!inFileH)
	{
		cout << "ERROR: File could not be found or open..." << endl;

		return 0;
	}

	list holidayList;

	while (getline(inFileH, holidays))
	{
		holidayList.insertLast(holidays);
	}

	inFileH.close();
	inFileN.close();

	list waitingList;
	list bookingHoliday;
	list bookingMagician;

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

				holidayList.printLinkedList();
				cout << "Please enter the name of the holiday the customer wants: ";
				getline(cin, holidayName);
				cout << endl;

				if (magicianList.checkAvailable() == false)
				{
					cout << "There are no magicians available" << endl;
					cout << "Your name and holidays are currently on the waiting list..." << endl << endl;
					waitingList.insertLast(holidayName);
					waitingList.insertLast(customerName);

				}
				else
				{
					magician = magicianList.getAvailable();

					bookingHoliday.insertLast(customerName);
					bookingHoliday.insertLast(holidayName);
					bookingHoliday.insertLast(magician);

					bookingMagician.insertLast(magician);
					bookingMagician.insertLast(holidayName);

					string c = customerName;
					c.resize(20, ' ');
					string m = magician;
					m.resize(20, ' ');
					
					cout << "CUSTOMER: " << c << "	MAGICIAN: " << m << "HOLIDAY: " << holidayName << endl << endl;

					//bookingHoliday.printToOutputFile(outFile);
				}

				cout << "Would you like to schedule for another holiday? [1]YES [2]NO" << endl;
				cin >> userAgain;
			} while (userAgain == 1);

			//bookingHoliday.printListCus_Hol();
			bookingHoliday.printToOutputFile(outFile);
			outFile << "============= transaction made =============" << endl;
			bookingHoliday.printToOutputFile(scheduleFile);
			scheduleFile.close();

			break;
		case 2:
			system("CLS");

			cout << "Enter the name of the person you want to remove: ";
			getline(cin.ignore(), customerName);
			cout << endl;

			holidayList.printLinkedList();
			cout << "Enter the name of the holiday you want to remove: ";
			getline(cin, holidayName);
			cout << endl;

			magicianRelocated = bookingHoliday.getMagician(holidayName);
			bookingHoliday.removeNodeByName(customerName);
			bookingHoliday.removeNodeByName(holidayName);
			bookingHoliday.removeNodeByName(magicianRelocated);

			bookingMagician.removeNodeByName(holidayName);
			bookingMagician.removeNodeByName(magicianRelocated);

			cout << customerName << " and " << holidayName << " were successfully removed from Schedule" << endl << endl;

			if (waitingList.getCount() != 0)
			{
				if (waitingList.checkHolidayWaiting(holidayName) == true)
				{
					waitingCustomer = waitingList.getCustomerWaiting(holidayName);
					waitingList.removeNodeByName(holidayName);
					waitingList.removeNodeByName(waitingCustomer);
					//Inserting customer on waiting list into schedule.
					bookingHoliday.insertLast(waitingCustomer);
					bookingHoliday.insertLast(holidayName);
					bookingHoliday.insertLast(magicianRelocated);
					//Updating magician's schedule.
					bookingMagician.insertLast(magicianRelocated);
					bookingMagician.insertLast(holidayName);

					cout << "Customer " << waitingCustomer << " is on the waiting list for " << holidayName << endl;
					cout << "Adding " << waitingCustomer << " to the schedule" << endl;
					system("pause");
				}
				else
				{
					string customerN = waitingList.getFirstData();
					waitingList.removeNodeByName(customerN);

					string holidayN = waitingList.getFirstData();
					waitingList.removeNodeByName(holidayN);

					bookingHoliday.insertLast(customerN);
					bookingHoliday.insertLast(holidayN);
					bookingHoliday.insertLast(magicianRelocated);

					bookingMagician.insertLast(magicianRelocated);
					bookingMagician.insertLast(holidayN);

					cout << "Customer " << customerN << " is next on the waiting list" << endl;
					cout << "Adding " << customerN << " to the schedule...";
					system("pause");
				}
			}

			bookingHoliday.printToOutputFile(outFile);
			outFile << "============= transaction made =============" << endl;

			scheduleFile.open("Schedule.txt", ios::out | ios::trunc);
			bookingHoliday.printToOutputFile(scheduleFile);
			scheduleFile.close();

			break;
		case 3:
			system("CLS");

			cout << "Enter the name of the new Magician: ";
			getline(cin.ignore(), newMagician);
			cout << endl;

			magicianList.insertLast(newMagician);

			cout << newMagician << " has been added to the Magician list!" << endl;

			system("pause");
			break;
		case 4:
			system("CLS");

			cout << "Enter the name of the magician who is dropping out: ";
			getline(cin.ignore(), dropOutMagician);
			cout << endl;

			magicianList.removeNodeByName(dropOutMagician);
			
			redistCustomer = bookingHoliday.getCustomerByMagician(dropOutMagician);
			redistHoliday = bookingHoliday.getHolidayByMagician(dropOutMagician);

			bookingHoliday.removeNodeByName(dropOutMagician);
			bookingHoliday.removeNodeByName(redistCustomer);
			bookingHoliday.removeNodeByName(redistHoliday);

			if (magicianList.checkAvailable() == true)
			{
				magician = magicianList.getAvailable();

				bookingHoliday.insertLast(redistCustomer);
				bookingHoliday.insertLast(redistHoliday);
				bookingHoliday.insertLast(magician);

				cout << "Since " << dropOutMagician << " left, " << redistCustomer << " and " << redistHoliday
					<< " would be given to " << magician << endl << endl;

				system("pause");
			}
			else
			{
				cout << "No available Magician at this moment." << endl;
				cout << redistCustomer << " and " << redistHoliday << " got moved to the waiting list..." << endl << endl;

				system("pause");
			}

			break;
		case 5:
			system("CLS");
			
			string space = " ";
			space.resize(20, ' ');
			cout << space << "[1] Search By Magician";
			cout << space << "[2] Search By Holiday" << endl << endl;
			cout << "Which Search Option you would like: ";
			cin >> userOption;

			switch (userOption)
			{
			case 1:
				break;
			case 2:
				break;

			default:
				break;
			}
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