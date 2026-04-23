//------------------------------------------------------------
// Class: UserAccountNode
// Purpose: Represents a single user account in a doubly linked list.
// Contains user details (username, password, birthday), and
// pointers to the next and previous accounts in the list.
//------------------------------------------------------------

class UserAccountNode {
public:
	string username;                  // User's chosen username
	string password;                  // User's password (should be hashed in practice)
	string birthday;                  // User's birthdate in MM/DD/YYYY format

	UserAccountNode* nextAccount;     // Pointer to the next node in the list
	UserAccountNode* previousAccount; // Pointer to the previous node in the list
};

//------------------------------------------------------------
// Function: printForward
// Purpose: Traverses the doubly linked list from head to tail,
// printing out the user account details.
//------------------------------------------------------------
void printForward(UserAccountNode* head) {
	UserAccountNode* traverser = head;

	// Iterate forward through the list
	while (traverser != nullptr) {
		cout << "Username: " << traverser->username << endl;
		cout << "Password: " << traverser->password << endl;
		cout << "Birthday of user: " << traverser->birthday << endl;
		cout << endl;

		traverser = traverser->nextAccount; // Move to next node
	}
}

//------------------------------------------------------------
// Function: printBackward
// Purpose: Traverses the doubly linked list from tail to head,
// printing out the user account details.
//------------------------------------------------------------
void printBackward(UserAccountNode* tail) {
	UserAccountNode* traverser = tail;

	// Iterate backward through the list
	while (traverser != nullptr) {
		cout << "Username: " << traverser->username << endl;
		cout << "Password: " << traverser->password << endl;
		cout << "Birthday of user: " << traverser->birthday << endl;
		cout << endl;

		traverser = traverser->previousAccount; // Move to previous node
	}
}
