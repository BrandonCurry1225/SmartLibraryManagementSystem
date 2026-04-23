#include <iostream>
#include <cstdlib>

using namespace std;

//--------------------------------------------------------------
// Class: BST
// Purpose: Implements a Binary Search Tree for storing book recommendations.
// Each node contains an ISBN (int) and a book title (string).
// Tree is sorted by ISBN.
//--------------------------------------------------------------
class BST {
private:

	// Node structure representing each book
	struct node {
		int ISBN;
		string BookTitle;
		node* left;   // Pointer to left child
		node* right;  // Pointer to right child
	};

	node* root; // Pointer to the root of the tree

public:

	//--------------------------------------------------------------
	// Constructor initializes root to null (empty tree)
	//--------------------------------------------------------------
	BST() {
		root = nullptr;
	}

	//--------------------------------------------------------------
	// Function: CreateLeaf
	// Purpose: Creates and returns a new node with given ISBN and title
	//--------------------------------------------------------------
	node* CreateLeaf(int ISBN, string BookTitle) {
		node* n = new node;
		n->ISBN = ISBN;
		n->BookTitle = BookTitle;
		n->left = nullptr;
		n->right = nullptr;
		return n;
	}

	//--------------------------------------------------------------
	// Function: AddLeaf
	// Public wrapper to insert a new node into the BST
	//--------------------------------------------------------------
	void AddLeaf(int ISBN, string BookTitle) {
		AddLeafPrivate(ISBN, BookTitle, root);
	}

	//--------------------------------------------------------------
	// Function: AddLeafPrivate
	// Purpose: Recursively inserts a node into the BST.
	// Keeps tree ordered by ISBN.
	//--------------------------------------------------------------
	void AddLeafPrivate(int ISBN, string BookTitle, node* Ptr) {
		// If tree is empty, set new node as root
		if (root == nullptr) {
			root = CreateLeaf(ISBN, BookTitle);
		}
		// Insert to the left subtree if ISBN is less
		else if (ISBN < Ptr->ISBN) {
			if (Ptr->left != nullptr) {
				AddLeafPrivate(ISBN, BookTitle, Ptr->left);
			}
			else {
				Ptr->left = CreateLeaf(ISBN, BookTitle);
			}
		}
		// Insert to the right subtree if ISBN is greater
		else if (ISBN > Ptr->ISBN) {
			if (Ptr->right != nullptr) {
				AddLeafPrivate(ISBN, BookTitle, Ptr->right);
			}
			else {
				Ptr->right = CreateLeaf(ISBN, BookTitle);
			}
		}
		// If ISBN already exists in the tree
		else {
			cout << "The ISBN " << ISBN << " has already been added to the tree\n";
		}
	}

	//--------------------------------------------------------------
	// Function: PrintInOrder
	// Purpose: Initiates in-order traversal to print tree contents
	//--------------------------------------------------------------
	void PrintInOrder() {
		PrintInOrderPrivate(root);
	}

	//--------------------------------------------------------------
	// Function: PrintInOrderPrivate
	// Purpose: Performs in-order traversal recursively
	// Prints nodes in ascending ISBN order
	//--------------------------------------------------------------
	void PrintInOrderPrivate(node* Ptr) {
		// Only proceed if the tree is not empty
		if (root != nullptr) {
			// Traverse left subtree
			if (Ptr->left != nullptr) {
				PrintInOrderPrivate(Ptr->left);
			}

			// Print current node
			cout << "ISBN: " << Ptr->ISBN << ", Book Title: " << Ptr->BookTitle << endl;

			// Traverse right subtree
			if (Ptr->right != nullptr) {
				PrintInOrderPrivate(Ptr->right);
			}
		}
		else {
			cout << "The tree is empty" << endl;
		}
	}
};