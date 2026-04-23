#include <iostream>
#include <queue>

using namespace std;

//-------------------------------------------------------------
// Class: BorrowedBooksQueue
// Purpose: Manages the list of borrowed books using a queue.
// Each book is represented by its ISBN (integer).
//-------------------------------------------------------------
class BorrowedBooksQueue {
public:
	queue<int> BorrowedISBNBooks; // Queue to store borrowed book ISBNs

	//-------------------------------------------------------------
	// Function: returnSize
	// Purpose: Displays the number of books currently in the queue.
	//-------------------------------------------------------------
	void returnSize() const {
		cout << "size: " << BorrowedISBNBooks.size() << endl;
	}

	//-------------------------------------------------------------
	// Function: BorrowedBooksIsEmpty
	// Purpose: Checks if any books are currently borrowed.
	// If not, displays a message. If yes, prints the queue.
	//-------------------------------------------------------------
	void BorrowedBooksIsEmpty() const {
		if (BorrowedISBNBooks.empty()) {
			cout << "There are currently no borrowed books" << endl;
		}
		else {
			cout << "Books that are currently checked out: " << endl;
			printBorrowedBooksList(); // Show borrowed books
		}
	}

	//-------------------------------------------------------------
	// Function: CheckOutBook
	// Purpose: Adds a book's ISBN to the queue (borrowing a book).
	//-------------------------------------------------------------
	void CheckOutBook(int ISBN) {
		BorrowedISBNBooks.push(ISBN);
	}

	//-------------------------------------------------------------
	// Function: RemoveSpecificISBN
	// Purpose: Removes a specific ISBN from the borrowed queue.
	// If the ISBN is found, it's removed and a message is printed.
	// Otherwise, a message is shown that the book wasn't found.
	//-------------------------------------------------------------
	void RemoveSpecificISBN(int ISBN) {
		queue<int> tempQueue; // Temporary queue to hold remaining books
		bool found = false;

		// Traverse the original queue
		while (!BorrowedISBNBooks.empty()) {
			if (BorrowedISBNBooks.front() == ISBN && !found) {
				// Skip the book we're removing (only the first match)
				cout << "Book with ISBN " << ISBN << " has been returned." << endl;
				found = true;
			}
			else {
				// Push other ISBNs to the temp queue
				tempQueue.push(BorrowedISBNBooks.front());
			}
			BorrowedISBNBooks.pop(); // Remove the front element
		}

		// Notify if ISBN wasn't found
		if (!found) {
			cout << "Book with ISBN " << ISBN << " was not found in the queue." << endl;
		}

		// Replace the original queue with the updated one
		BorrowedISBNBooks = tempQueue;
	}

	//-------------------------------------------------------------
	// Function: printBorrowedBooksList
	// Purpose: Prints all currently borrowed book ISBNs in order.
	//-------------------------------------------------------------
	void printBorrowedBooksList() const {
		queue<int> temp = BorrowedISBNBooks; // Copy to avoid modifying original queue
		while (!temp.empty()) {
			cout << "ISBN: " << temp.front() << " ";
			temp.pop();
		}
		cout << endl;
	}
};