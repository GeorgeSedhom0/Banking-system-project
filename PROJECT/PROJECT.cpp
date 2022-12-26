#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#define RESET "\033[0m"
#define BOLDGREEN "\033[1m\033[32m"
#define BOLDWHITE "\033[1m\033[37m"
#define BOLDRED "\033[1m\033[31m"
using namespace std;

// project for basic banking system using linked list will have options
// E for enqueuing
// D for dequeuing
// S for searching
// U for updating
// P for printing
//  where PA for printing all
//  where PV for printing VIPs only
//  where PN for printing normal customers only
// R to remove all saved data 
//   where RA for removing all
//   where RF for removing data from file only
//   where RM for removing data from memory only
// Q for quitting

struct node {
	string name;
	int age;
	int accountNumber;
	int balance;
	bool VIP;
	node* next;
};

node* first = NULL;
node* last = NULL;


// interface for all the functions
void enqueue(string name, int age, int balance, bool VIP);
void dequeue();
void search(int accountNumber);
void print(char mode);
void update(int accountNumber, string name, int age, int balance, bool VIP);
void getUserInput();
void saveToFile();
void loadFromFile();



int main()
{
	loadFromFile();
	getUserInput();
}

void doMore() {
	// wait till the user presses enter then call getUserInput
	cout << endl << "Opiration Completed!" << endl;
	cout << "Press enter to continue...";
	cin.ignore();
	cin.get();
	getUserInput();
}

void saveToFile() {
	// save the linked list to a file

	ofstream file;
	file.open("data.txt", ios::trunc);

	// if file is not empty remove all the data in the file

	node* temp = first;

	while (temp != NULL) {
		file << endl;
		file << temp->name << endl;
		file << temp->age << endl;
		file << temp->balance << endl;
		if (temp->VIP) {
			file << "true";
		}
		else {
			file << "false";
		}
		temp = temp->next;
	}

	file.close();
}

void loadFromFile() {
	// get the linked list from a file

	ifstream file;
	file.open("data.txt");

	string name;
	int age;
	int balance;
	bool VIP;
	string vip;

	// if the file is empty early return
	file.seekg(0, ios::end);
	if (file.tellg() == 0) {
		return;
	}
	else {
		file.seekg(0, ios::beg);
	}

	while (file.good()) {
		file >> name;
		file >> age;
		file >> balance;
		file >> vip;
		if (vip == "true") {
			VIP = true;
		}
		else {
			VIP = false;
		}
		enqueue(name, age, balance, VIP);
	}
	file.close();
}

bool isEmpty() {
	if (first == NULL) {
		return true;
	}
	else {
		return false;
	}
}

int queueLength() {
	int length = 0;
	node* temp = first;
	while (temp != NULL) {
		length++;
		temp = temp->next;
	}
	return length;
}

void enqueue(string name, int age, int balance, bool VIP) {
	node* temp = new node;
	temp->name = name;
	temp->age = age;
	temp->accountNumber = queueLength();
	temp->balance = balance;
	temp->VIP = VIP;
	temp->next = NULL;
	if (isEmpty()) {
		first = temp;
		last = temp;
	}
	else {
		last->next = temp;
		last = temp;
	}
}

// the update function should update the givven account number with all the new data
void update(int accountNumber, string name, int age, int balance, bool VIP) {
	node* temp = first;
	while (temp != NULL) {
		if (temp->accountNumber == accountNumber) {
			temp->name = name;
			temp->age = age;
			temp->balance = balance;
			temp->VIP = VIP;
			break;
		}
		temp = temp->next;
	}
	saveToFile();
	doMore();
}

void dequeue() {
	if (isEmpty()) {
		cout << "No customers in queue" << endl;
	}
	else {
		node* temp = first;
		first = first->next;
		delete temp;
	}
	doMore();
}

void remove(char mode) {
	if (mode == 'A' || mode == 'a') {
		// remove data from file only
		ofstream file;
		file.open("data.txt", ios::trunc);
		file.close();
		// remove data from memory only
		node* temp = first;
		while (temp != NULL) {
			node* toBeRemoved = temp;
			temp = temp->next;
			first = temp;
			delete toBeRemoved;
		}
	}
	else if (mode == 'F' || mode == 'f') {
		// remove data from file only
		ofstream file;
		file.open("data.txt", ios::trunc);
		file.close();
	}
	else if (mode == 'M' || mode == 'm') {
		// remove data from memory only
		node* temp = first;
		while (temp != NULL) {
			node* toBeRemoved = temp;
			temp = temp->next;
			first = temp;
			delete toBeRemoved;
		}
	}
	else {
		cout << "Invalid mode" << endl;
		cout << "Valid modes are A, F, M" << endl;
	}
	doMore();
}

void sort(int mode) {
	// sort the linked list
	// mode 1 for sorting by name
	// mode 2 for sorting by age
	// mode 3 for sorting by account number
	// mode 4 for sorting by balance
	// will use selection sort for fast sorting

	node* temp = first;
	node* min = first;

	while (temp != NULL) {
		min = temp;
		node* temp2 = temp->next;
		while (temp2 != NULL) {
			if (mode == 1) {
				if (temp2->name < min->name) {
					min = temp2;
				}
			}
			else if (mode == 2) {
				if (temp2->age < min->age) {
					min = temp2;
				}
			}
			else if (mode == 3) {
				if (temp2->accountNumber < min->accountNumber) {
					min = temp2;
				}
			}
			else if (mode == 4) {
				if (temp2->balance < min->balance) {
					min = temp2;
				}
			}
			temp2 = temp2->next;
		}
		// swap the data
		string name = temp->name;
		int age = temp->age;
		int accountNumber = temp->accountNumber;
		int balance = temp->balance;
		bool VIP = temp->VIP;

		temp->name = min->name;
		temp->age = min->age;
		temp->accountNumber = min->accountNumber;
		temp->balance = min->balance;
		temp->VIP = min->VIP;

		min->name = name;
		min->age = age;
		min->accountNumber = accountNumber;
		min->balance = balance;
		min->VIP = VIP;

		temp = temp->next;
	}
}

void print(char mode) {

	cout << endl << "How would you like the data to be Sorted" << endl;
	cout << "1. By Account Number" << endl;
	cout << "2. By Name" << endl;
	cout << "3. By Age" << endl;
	cout << "4. By Balance" << endl;

	int choice;
	cin >> choice;
	if (choice == 1) {
		sort(3);
	}
	else if (choice == 2) {
		sort(1);
	}
	else if (choice == 3) {
		sort(2);
	}
	else if (choice == 4) {
		sort(4);
	}
	else {
		cout << "Printing data without sorting" << endl;
	}
	// clear the console for the data to be clear
	system("cls");
	if (mode == 'a') {
		node* temp = first;
		while (temp != NULL) {
			cout << BOLDGREEN;
			cout << setw(25) << left << "      Name: " << temp->name << endl;
			cout << setw(25) << left << "      Age: " << temp->age << endl;
			cout << setw(25) << left << "      Account Number: " << temp->accountNumber << endl;
			cout << setw(25) << left << "      Balance: " << temp->balance << endl;
			cout << setw(25) << left << "      VIP: " << temp->VIP << endl;
			cout << BOLDRED << "_________________________________" << RESET << endl;
			cout << endl;
			temp = temp->next;
		}
	}
	else if (mode == 'v') {
		node* temp = first;
		while (temp != NULL) {
			if (temp->VIP == true) {
				cout << BOLDGREEN;
				cout << setw(25) << left << "      Name: " << temp->name << endl;
				cout << setw(25) << left << "      Age: " << temp->age << endl;
				cout << setw(25) << left << "      Account Number: " << temp->accountNumber << endl;
				cout << setw(25) << left << "      Balance: " << temp->balance << endl;
				cout << setw(25) << left << "      VIP: " << temp->VIP << endl;
				cout << BOLDRED << "_________________________________" << RESET << endl;
				cout << endl;
			}
			temp = temp->next;
		}
	}
	else if (mode == 'n') {
		node* temp = first;
		while (temp != NULL) {
			if (temp->VIP == false) {
				cout << BOLDGREEN;
				cout << setw(25) << left << "      Name: " << temp->name << endl;
				cout << setw(25) << left << "      Age: " << temp->age << endl;
				cout << setw(25) << left << "      Account Number: " << temp->accountNumber << endl;
				cout << setw(25) << left << "      Balance: " << temp->balance << endl;
				cout << setw(25) << left << "      VIP: " << temp->VIP << endl;
				cout << BOLDRED << "_________________________________" << RESET << endl;
				cout << endl;
			}
			temp = temp->next;
		}
	}
	else {
		cout << "Invalid choice" << endl;
		cout << "Your input was " << mode << endl;
		cout << "Valid inputs are a, v, n" << endl;
	}
	doMore();
}

void search(int mode) {
	node* temp = first;
	string name = "";
	int age = 0;
	int balance = 0;
	int accountNumber = 0;

	if (mode == 1) {
		cout << "Enter the name of the person you want to search for: ";
		cin >> name;
	}
	else if (mode == 2) {
		cout << "Enter the age of the person you want to search for: ";
		cin >> age;
	}
	else if (mode == 3) {
		cout << "Enter the balance of the person you want to search for: ";
		cin >> balance;
	}
	else if (mode == 4) {
		cout << "Enter the account number of the person you want to search for: ";
		cin >> accountNumber;
	}
	else {
		cout << "Invalid choice" << endl;
		cout << "Your input was " << mode << endl;
		cout << "Valid inputs are 1, 2, 3, 4" << endl;
		doMore();
		return;
	}
	
	while (temp != NULL) {
		bool areEqual;
		if (mode == 1) {
			areEqual = (temp->name == name);
		}
		else if (mode == 2) {
			areEqual = (temp->age == age);
		}
		else if (mode == 3) {
			areEqual = (temp->balance == balance);
		}
		else if (mode == 4) {
			areEqual = (temp->accountNumber == accountNumber);
		}
		
		if (areEqual) {
			cout << BOLDGREEN;
			cout << setw(25) << left << "      Name: " << temp->name << endl;
			cout << setw(25) << left << "      Age: " << temp->age << endl;
			cout << setw(25) << left << "      Account Number: " << temp->accountNumber << endl;
			cout << setw(25) << left << "      Balance: " << temp->balance << endl;
			cout << setw(25) << left << "      VIP: " << temp->VIP << endl;
			cout << BOLDRED << "_________________________________" << RESET << endl;
			cout << endl;
		}
		temp = temp->next;
	}
	cout << "No customer with that account number" << endl;
	doMore();
}

void getUserInput() {
	// first clear the console from any previues opitarions 
	system("cls");
	// print the menu
	cout
		<< left
		<< setw(20)
		<< "Code to use"
		<< left
		<< setw(10)
		<< BOLDWHITE
		<< "What it will do"
		<< RESET
		<< endl;

	cout
		<< left
		<< setw(20)
		<< "     E"
		<< left
		<< setw(10)
		<< BOLDGREEN
		<< "for enqueuing"
		<< RESET
		<< endl;

	cout
		<< left
		<< setw(20)
		<< "     D"
		<< left
		<< setw(10)
		<< BOLDGREEN
		<< "for dequeuing"
		<< RESET
		<< endl;

	cout
		<< left
		<< setw(20)
		<< "     P"
		<< left
		<< setw(10)
		<< BOLDGREEN
		<< "for printing"
		<< RESET
		<< endl;

	cout
		<< left
		<< setw(20)
		<< "     S"
		<< left
		<< setw(10)
		<< BOLDGREEN
		<< "for searching"
		<< RESET
		<< endl;

	cout
		<< left
		<< setw(20)
		<< "     U"
		<< left
		<< setw(10)
		<< BOLDGREEN
		<< "for updating"
		<< RESET
		<< endl;

	cout
		<< left
		<< setw(20)
		<< "     R"
		<< left
		<< setw(10)
		<< BOLDGREEN
		<< "for removing"
		<< RESET
		<< endl;

	cout
		<< left
		<< setw(20)
		<< "     Q"
		<< left
		<< setw(10)
		<< BOLDGREEN
		<< "for quitting"
		<< RESET
		<< endl;

	cout << BOLDWHITE;
	cout << "Enter your choice: ";

	// get the user input
	char input;
	cin >> input;
	// check the input

	if (input == 'e' || input == 'E') {
		// get the data from the user
		string name;
		int age;
		int balance;
		bool VIP;
		cout << "Enter the name: ";
		cin >> name;
		cout << "Enter the age: ";
		cin >> age;
		cout << "Enter the balance: ";
		cin >> balance;
		string vip;
		cout << "Enter VIP status (V for VIP/ anything else for Not VIP): ";
		cin >> vip;
		if (vip == "V" || vip == "v") {
			VIP = true;
		}
		else {
			VIP = false;
		}
		// enqueue the data
		cout << RESET;
		enqueue(name, age, balance, VIP);
		saveToFile();
		doMore();
	}
	else if (input == 'd' || input == 'D') {
		// dequeue the data
		cout << RESET;
		dequeue();
	}
	else if (input == 's' || input == 'S') {
		// get the account number from the user
		int mode;
		cout << "How would you like to search" << endl;
		cout << "1. By name" << endl;
		cout << "2. By age" << endl;
		cout << "3. By balance" << endl;
		cout << "4. By account number" << endl;
		cin >> mode;
		cout << RESET;
		// search for the account number
		search(mode);
	}
	else if (input == 'p' || input == 'P') {
		// get the mode from the user
		char mode;
		cout << "You can print all the customers (a), VIP customers (v) or non-VIP customers (n): ";
		cout << "Enter the mode: ";
		cin >> mode;
		cout << RESET;
		// print the data
		print(mode);
	}
	else if (input == 'u' || input == 'U') {
		// get the data from the user
		int accountNumber;
		string name;
		int age;
		int balance;
		bool VIP;
		cout << "Enter the account number: ";
		cin >> accountNumber;
		cout << "Enter the name: ";
		cin >> name;
		cout << "Enter the age: ";
		cin >> age;
		cout << "Enter the balance: ";
		cin >> balance;
		cout << "Enter VIP status (V) for VIP anything else for not VIP: ";
		string vip;
		cin >> vip;
		if (vip == "v" || vip == "V") {
			VIP = true;
		}
		else {
			VIP = false;
		}
		cout << RESET;
		// update the data
		update(accountNumber, name, age, balance, VIP);
	}
	else if (input == 'q' || input == 'Q') {
		// quit the program
		cout << RESET;
		exit(0);
	}
	else if (input == 'r' || input == 'R') {
		char mode;
		cout << "You can remove all the app data (a), from current memmory only(m), from saced file only(f)";
		cin >> mode;
		cout << RESET;
		remove(mode);
	}
	else {
		// print error message
		cout << "Invalid input" << endl;
		cout << "Do you want to try again? (Y/N): ";
		char tryAgain;
		cin >> tryAgain;
		cout << RESET;
		if (tryAgain == 'Y' || tryAgain == 'y') {
			getUserInput();
		}
		else {
			exit(0);
		}
	}
	doMore();
}



