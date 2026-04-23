#include <iostream>
#include <stack>
#include <string>
#include <chrono>
#include <ctime>

using namespace std;

//--------------------------------------------------------------
// Class: UserActivityStack
// Purpose: Logs user activities with timestamps using a stack.
// Allows adding and printing recent activities in LIFO order.
//--------------------------------------------------------------
class UserActivityStack {

private:
	// Internal structure to store each activity and its timestamp
	struct ActivityEntry {
		string activity;    // Description of the user action
		string timestamp;   // Time when the action was recorded
	};

public:
	// Stack to store user activity log entries (most recent on top)
	stack<ActivityEntry> UserActivityLog;

	//--------------------------------------------------------------
	// Function: getCurrentTimestamp
	// Purpose: Gets the current date and time as a formatted string
	//--------------------------------------------------------------
	string getCurrentTimestamp() {
		auto now = chrono::system_clock::now();                   // Get current time
		time_t now_time = chrono::system_clock::to_time_t(now);  // Convert to time_t format
		char buffer[26];
		ctime_s(buffer, sizeof(buffer), &now_time);              // Safe version of ctime
		buffer[strcspn(buffer, "\n")] = '\0';                     // Remove newline character
		return string(buffer);                                   // Return as string
	}

	//--------------------------------------------------------------
	// Function: AddRecentUserActivity
	// Purpose: Adds a new user activity and timestamp to the stack
	//--------------------------------------------------------------
	void AddRecentUserActivity(const string& UserActivity) {
		ActivityEntry entry;
		entry.activity = UserActivity;
		entry.timestamp = getCurrentTimestamp();
		UserActivityLog.push(entry); // Push onto top of stack
	}

	//--------------------------------------------------------------
	// Function: printStackElements
	// Purpose: Prints all activities in reverse order (most recent first)
	// Note: Uses a temporary stack to avoid destroying original stack
	//--------------------------------------------------------------
	void printStackElements() {
		stack<ActivityEntry> tempStack = UserActivityLog; // Copy stack for safe traversal

		while (!tempStack.empty()) {
			ActivityEntry entry = tempStack.top(); // Access top activity
			cout << "[" << entry.timestamp << "] " << entry.activity << endl;
			tempStack.pop(); // Remove top activity from temp stack
		}
	}
};