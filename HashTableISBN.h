#include <iostream>
#include <list>
#include <cstring>
#include <vector>

using namespace std;

//-----------------------------------------------------------
// Class: LibraryInventoryHashTable
// Purpose: Manage books using a hash table based on ISBN numbers.
// Uses separate chaining (list of pairs) to handle collisions.
//-----------------------------------------------------------
class LibraryInventoryHashTable {
private:
	static const int ISBNHashGroup = 11; // Total number of hash buckets
	list<pair<int, string>> table[ISBNHashGroup]; // Hash table with ISBN-title pairs

public:

	//-----------------------------------------------------------
	// Checks if the hash table is empty by summing all bucket sizes.
	//-----------------------------------------------------------
	bool isEmpty() const {
		int sum{};
		for (int i{}; i < ISBNHashGroup; i++) {
			sum += table[i].size(); // Add size of each list
		}
		return (sum == 0);
	}

	//-----------------------------------------------------------
	// Hash Function: Computes bucket index for a given ISBN
	// Uses modulo operation.
	//-----------------------------------------------------------
	int hashFunction(int ISBN) {
		return ISBN % ISBNHashGroup;
	}

	//-----------------------------------------------------------
	// Inserts a new ISBN and book title into the hash table.
	// If ISBN already exists, updates the title instead.
	//-----------------------------------------------------------
	void insertISBN(int ISBN, string BookTitle) {
		int hashValue = hashFunction(ISBN); // Get bucket index
		auto& cell = table[hashValue];      // Reference to the list in that bucket
		auto bItr = begin(cell);
		bool ISBNExists = false;

		// Check if ISBN already exists in this bucket
		for (; bItr != end(cell); bItr++) {
			if (bItr->first == ISBN) {
				ISBNExists = true;
				bItr->second = BookTitle; // Replace existing title
				cout << "ISBN Exists and book title will be replaced" << endl;
				break;
			}
		}

		// If ISBN not found, insert as a new entry
		if (!ISBNExists) {
			cell.emplace_back(ISBN, BookTitle);
		}
	}

	//-----------------------------------------------------------
	// Removes a book from the hash table using the ISBN.
	// If ISBN is not found, prints a message.
	//-----------------------------------------------------------
	void removeISBN(int ISBN) {
		int hashValue = hashFunction(ISBN);  // Get bucket index
		auto& cell = table[hashValue];       // Reference to the list
		auto bItr = begin(cell);
		bool ISBNExists = false;

		// Search for the ISBN in the list
		for (; bItr != end(cell); bItr++) {
			if (bItr->first == ISBN) {
				ISBNExists = true;
				bItr = cell.erase(bItr);  // Remove entry
				cout << "ISBN removed." << endl;
				break;
			}
		}

		if (!ISBNExists) {
			cout << "ISBN not found and could not be removed." << endl;
		}
	}

	//-----------------------------------------------------------
	// Prints all ISBN and book title pairs in the hash table.
	// Skips empty buckets.
	//-----------------------------------------------------------
	void printISBNTable() {
		for (int i{}; i < ISBNHashGroup; i++) {
			if (table[i].size() == 0) continue; // Skip empty buckets

			auto bItr = table[i].begin();
			for (; bItr != table[i].end(); bItr++) {
				cout << "ISBN: " << bItr->first << ", Title: " << bItr->second << endl;
			}
		}
	}
};