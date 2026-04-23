// Include all relevant header files for the library system components

#include "HashTableISBN.h"              // Manages book inventory using hash table
#include "UserAccountDLL.h"             // Doubly linked list for user accounts
#include "BookBorrowingQueue.h"         // Queue for managing borrowed books
#include "BSTBookRecommendation.h"      // BST for book recommendation system
#include "UserActivityLogStack.h"       // Stack to store user activity log

#include <iostream>
#include <cstdlib>
#include <stack>
#include <list>
#include <cstring>
#include <queue>
#include <limits>
#include <iomanip>

using namespace std;

//--------------------------------------------------------------------
// Global variables shared across the system
//--------------------------------------------------------------------

string username, password, birthday, BookTitle;
int ISBN;
BorrowedBooksQueue BorrowedBooksList;   // Queue for borrowed books
LibraryInventoryHashTable LibraryInventory; // Hash table for book inventory
UserAccountNode* head; // Start of the doubly linked list for user accounts
UserAccountNode* tail; // End of the doubly linked list for user accounts
BST myTree; // Book recommendation tree (BST)
UserActivityStack UserActivity; // Stack for user activity logging

//--------------------------------------------------------------------
// Function to display recent user activities from the activity stack
//--------------------------------------------------------------------
void ViewRecentUserActivity() {
	UserActivity.printStackElements();
	cout << endl;
}

//--------------------------------------------------------------------
// Display all user accounts stored in the linked list
//--------------------------------------------------------------------
void ViewUserAccounts() {
	UserActivity.AddRecentUserActivity("User viewed recent accounts");

	cout << "User accounts as of current: " << endl;
	cout << endl;
	printForward(head);
	cout << endl;
}

//--------------------------------------------------------------------
// Function to insert a book into the hash table inventory
//--------------------------------------------------------------------
void InsertBookInventory() {
	cout << "Insert Book ISBN and title" << endl;
	cout << "ISBN: ";
	cin >> ISBN;
	cout << endl;

	cout << "Book Title: ";
	cin.ignore();               // To allow multi-word book titles
	getline(cin, BookTitle);
	cout << endl;

	LibraryInventory.hashFunction(ISBN);
	LibraryInventory.insertISBN(ISBN, BookTitle);
	UserActivity.AddRecentUserActivity("User added book to inventory");
}

//--------------------------------------------------------------------
// Displays the current books available in the inventory
//--------------------------------------------------------------------
void ViewBookInventory() {
	cout << "Current Books in inventory: " << endl;
	cout << endl;

	LibraryInventory.printISBNTable();
	UserActivity.AddRecentUserActivity("User viewed books in inventory");
}

//--------------------------------------------------------------------
// Allows user to check out a book by its ISBN
//--------------------------------------------------------------------
void CheckOutBook() {
	cout << "What book would you like to check out?:" << endl;
	cout << endl;

	ViewBookInventory(); // Display inventory for reference

	cout << endl;
	cout << "ISBN: ";
	cin >> ISBN;
	cout << endl;

	BorrowedBooksList.CheckOutBook(ISBN);     // Add to borrowed books queue
	LibraryInventory.removeISBN(ISBN);        // Remove from inventory

	cout << endl;
	cout << "Book has been successfully checked out" << endl;
	UserActivity.AddRecentUserActivity("User checked out a book");
	cout << endl;
}

//--------------------------------------------------------------------
// Allows user to check in a book (return it)
//--------------------------------------------------------------------
void CheckInBook() {
	cout << "What book would you like to check in?:" << endl;
	cout << endl;

	BorrowedBooksList.printBorrowedBooksList();  // Show borrowed books

	cout << "ISBN: ";
	cin >> ISBN;
	cout << endl;

	cout << "Book Title: ";
	cin.ignore();
	getline(cin, BookTitle);
	cout << endl;

	LibraryInventory.insertISBN(ISBN, BookTitle);   // Return book to inventory
	BorrowedBooksList.RemoveSpecificISBN(ISBN);     // Remove from borrowed queue

	cout << "Book has been successfully checked in" << endl;
	cout << endl;
	UserActivity.AddRecentUserActivity("User returned a book");
}

//--------------------------------------------------------------------
// Prints a visual separator line in the UI using setfill and setw
//--------------------------------------------------------------------
void printSeparator(char symbol = '=', int width = 50) {
	cout << setfill(symbol) << setw(width) << "" << setfill(' ') << endl;
}

//--------------------------------------------------------------------
// Displays main menu and handles user navigation through options
//--------------------------------------------------------------------
void ViewMenuOptions() {
	int Useroption;

	while (true) {
		system("cls"); // Clear console screen (Windows only)

		// Display main menu UI
		cout << "==============================================" << endl;
		cout << "         Smart Library Management Menu       " << endl;
		cout << "==============================================" << endl;
		cout << " 1.   View User Accounts" << endl;
		cout << " 2.   Insert Book into Inventory" << endl;
		cout << " 3.   View Current Books in Inventory" << endl;
		cout << " 4.   Check Out a Book" << endl;
		cout << " 5.   Check In a Book" << endl;
		cout << " 6.   Create New Student Account" << endl;
		cout << " 7.   View Book Recommendations" << endl;
		cout << " 8.   View Your Checked Out Books" << endl;
		cout << " 9.   View Recent User Activity" << endl;
		cout << " 0.   Exit Program" << endl;
		cout << "----------------------------------------------" << endl;
		cout << " Please choose an option (0-9): ";

		cin >> Useroption;

		// Handle non-numeric input
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\n? Invalid input. Please enter a number from 0 to 9.\n";
			system("pause");
			continue;
		}

		cout << endl;

		switch (Useroption) {
		case 1:
			ViewUserAccounts();
			break;
		case 2:
			InsertBookInventory();
			break;
		case 3:
			ViewBookInventory();
			break;
		case 4:
			CheckOutBook();
			break;
		case 5:
			CheckInBook();
			break;
		case 6: {
			// Create a new student account
			cout << "Create a new student account\n" << endl;
			cout << "Username: ";
			cin >> username;
			cout << "Password: ";
			cin >> password;
			cout << "Birthday (MM/DD/YYYY): ";
			cin >> birthday;

			// Create and link new account node
			UserAccountNode* userAccount = new UserAccountNode();
			userAccount->username = username;
			userAccount->password = password;
			userAccount->birthday = birthday;
			userAccount->nextAccount = nullptr;
			userAccount->previousAccount = tail;

			if (tail != nullptr) {
				tail->nextAccount = userAccount;
				tail = userAccount;
			}
			else {
				head = tail = userAccount;
			}

			UserActivity.AddRecentUserActivity("User created a new account");
			cout << "\n Account successfully created!\n";
			break;
		}
		case 7:
			cout << " Your Book Recommendations:\n" << endl;
			myTree.PrintInOrder(); // Display BST in order
			break;
		case 8:
			cout << " Your Checked Out Books:\n" << endl;
			BorrowedBooksList.BorrowedBooksIsEmpty(); // Check if borrowed queue is empty
			break;
		case 9:
			cout << " Recent User Activity Log:\n" << endl;
			ViewRecentUserActivity(); // Display recent activity
			break;
		case 0:
			cout << " Thank you for using the Smart Library System. Goodbye!" << endl;
			exit(0); // Exit program
		default:
			cout << " Invalid option. Please choose between 0 and 9.\n";
			break;
		}

		// Pause and wait before returning to menu
		cout << "\nPress Enter to return to main screen.";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get();
	}
}

//--------------------------------------------------------------------
// Entry point for the Smart Library System
//--------------------------------------------------------------------
int main() {

	system("cls"); // Clear screen at start
	printSeparator();
	cout << setw(35) << " Smart Library System " << endl;
	printSeparator();
	cout << setw(35) << " Account Registration " << endl;
	printSeparator('-');

	// Prompt user for account details
	cout << "Please insert a username: ";
	getline(cin, username);
	while (username.empty()) {
		cout << "Username cannot be empty. Please enter again: ";
		getline(cin, username);
	}

	cout << "Please insert a unique password: ";
	getline(cin, password);
	while (password.empty()) {
		cout << "Password cannot be empty. Please enter again: ";
		getline(cin, password);
	}

	cout << "Please insert your birthday in format (MM/DD/YYYY): ";
	getline(cin, birthday);
	while (birthday.empty()) {
		cout << "Birthday cannot be empty. Please enter again: ";
		getline(cin, birthday);
	}

	// Create the initial user account (head/tail of DLL)
	UserAccountNode* userAccount = new UserAccountNode();
	userAccount->username = username;
	userAccount->password = password;
	userAccount->birthday = birthday;
	userAccount->nextAccount = nullptr;
	userAccount->previousAccount = nullptr;
	head = userAccount;
	tail = userAccount;

	UserActivity.AddRecentUserActivity("User created an account");

	// Launch main menu
	ViewMenuOptions();

	return 0;
}