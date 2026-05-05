#include <iostream>
#include <string>
#include <limits>
#include <regex>
using namespace std;

struct Node {
    int key;
    string value;
    Node* next;
    Node(int k, const string& v) : key(k), value(v), next(nullptr) {}
};

class HashTable {
private:
    static const int bucket = 10;
    Node* table[bucket];

public:
    HashTable() {
        for (int i = 0; i < bucket; i++)
            table[i] = nullptr;
    }

    ~HashTable() {
        for (int i = 0; i < bucket; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* toDelete = current;
                current = current->next;
                delete toDelete;
            }
            table[i] = nullptr;
        }
    }

    int hashFunction(int key) {
        return (key % bucket + bucket) % bucket; // handles negative keys safely
    }

    // Returns false if already marked present on that date
    bool markPresent(int rollNumber, const string& date) {
        if (wasPresent(rollNumber, date))
            return false;
        int index = hashFunction(rollNumber);
        Node* newNode = new Node(rollNumber, date);
        newNode->next = table[index];
        table[index] = newNode;
        return true;
    }

    int countPresent(int rollNumber) {
        int index = hashFunction(rollNumber);
        Node* current = table[index];
        int count = 0;
        while (current != nullptr) {
            if (current->key == rollNumber)
                count++;
            current = current->next;
        }
        return count;
    }

    bool wasPresent(int rollNumber, const string& date) {
        int index = hashFunction(rollNumber);
        Node* current = table[index];
        while (current != nullptr) {
            if (current->key == rollNumber && current->value == date)
                return true;
            current = current->next;
        }
        return false;
    }

    // Returns false if the record wasn't found
    bool removeDay(int rollNumber, const string& date) {
        int index = hashFunction(rollNumber);
        Node* current = table[index];
        Node* prev = nullptr;
        while (current != nullptr) {
            if (current->key == rollNumber && current->value == date) {
                if (prev == nullptr)
                    table[index] = current->next;
                else
                    prev->next = current->next;
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    // Returns false if the student had no records
    bool removeStudent(int rollNumber) {
        int index = hashFunction(rollNumber);
        Node* current = table[index];
        Node* prev = nullptr;
        bool found = false;
        while (current != nullptr) {
            if (current->key == rollNumber) {
                found = true;
                Node* toDelete = current;
                if (prev == nullptr) {
                    table[index] = current->next;
                    current = table[index];
                } else {
                    prev->next = current->next;
                    current = current->next;
                }
                delete toDelete;
            } else {
                prev = current;
                current = current->next;
            }
        }
        return found;
    }

    void display() {
        cout << "\n";
        for (int i = 0; i < bucket; i++) {
            cout << "[" << i << "] ";
            Node* current = table[i];
            if (current == nullptr) {
                cout << "(empty)\n";
                continue;
            }
            // FIX: old code printed first node's roll number then skipped it
            while (current != nullptr) {
                cout << "Roll " << current->key << " -> " << current->value << "  ";
                current = current->next;
            }
            cout << "\n";
        }
    }
};

// Safely reads an integer — clears cin on bad input
bool readInt(int& out) {
    if (!(cin >> out)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}

// Reads a non-empty trimmed string
bool readString(string& out) {
    getline(cin, out);
    // Trim leading/trailing spaces
    size_t start = out.find_first_not_of(" \t\r\n");
    size_t end   = out.find_last_not_of(" \t\r\n");
    if (start == string::npos) {
        out = "";
        return false;
    }
    out = out.substr(start, end - start + 1);
    return !out.empty();
}

// Validates YYYY-MM-DD format and basic range checks
bool isValidDate(const string& date) {
    regex pattern(R"(^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01])$)");
    return regex_match(date, pattern);
}

void printMenu() {
    cout << "\n============================\n";
    cout << "  Attendance System Menu\n";
    cout << "============================\n";
    cout << "1. Mark a student present\n";
    cout << "2. Count days a student was present\n";
    cout << "3. Check if student was present on a date\n";
    cout << "4. Remove a specific day for a student\n";
    cout << "5. Remove all records for a student\n";
    cout << "6. Display full attendance table\n";
    cout << "7. Exit\n";
    cout << "============================\n";
    cout << "Enter your choice: ";
}

int main() {
    HashTable h;
    int choice;

    do {
        printMenu();

        if (!readInt(choice)) {
            cout << "Invalid input. Please enter a number from 1 to 7.\n";
            continue;
        }

        if (choice == 1) {
            int rollNumber;
            string date;
            cout << "Enter roll number: ";
            if (!readInt(rollNumber) || rollNumber <= 0) {
                cout << "Invalid roll number. Must be a positive integer.\n";
                continue;
            }
            cout << "Enter date (YYYY-MM-DD): ";
            if (!readString(date) || !isValidDate(date)) {
                cout << "Invalid date format. Use YYYY-MM-DD (e.g. 2026-05-01).\n";
                continue;
            }
            if (!h.markPresent(rollNumber, date))
                cout << "Roll " << rollNumber << " is already marked present on " << date << ".\n";
            else
                cout << "Attendance marked for roll " << rollNumber << " on " << date << ".\n";

        } else if (choice == 2) {
            int rollNumber;
            cout << "Enter roll number: ";
            if (!readInt(rollNumber) || rollNumber <= 0) {
                cout << "Invalid roll number. Must be a positive integer.\n";
                continue;
            }
            cout << "Roll " << rollNumber << " was present "
                 << h.countPresent(rollNumber) << " day(s).\n";

        } else if (choice == 3) {
            int rollNumber;
            string date;
            cout << "Enter roll number: ";
            if (!readInt(rollNumber) || rollNumber <= 0) {
                cout << "Invalid roll number. Must be a positive integer.\n";
                continue;
            }
            cout << "Enter date (YYYY-MM-DD): ";
            if (!readString(date) || !isValidDate(date)) {
                cout << "Invalid date format. Use YYYY-MM-DD (e.g. 2026-05-01).\n";
                continue;
            }
            bool result = h.wasPresent(rollNumber, date);
            cout << "Roll " << rollNumber << " was "
                 << (result ? "" : "NOT ") << "present on " << date << ".\n";

        } else if (choice == 4) {
            int rollNumber;
            string date;
            cout << "Enter roll number: ";
            if (!readInt(rollNumber) || rollNumber <= 0) {
                cout << "Invalid roll number. Must be a positive integer.\n";
                continue;
            }
            cout << "Enter date to remove (YYYY-MM-DD): ";
            if (!readString(date) || !isValidDate(date)) {
                cout << "Invalid date format. Use YYYY-MM-DD (e.g. 2026-05-01).\n";
                continue;
            }
            if (!h.removeDay(rollNumber, date))
                cout << "No record found for roll " << rollNumber << " on " << date << ".\n";
            else
                cout << "Removed " << date << " for roll " << rollNumber << ".\n";

        } else if (choice == 5) {
            int rollNumber;
            cout << "Enter roll number: ";
            if (!readInt(rollNumber) || rollNumber <= 0) {
                cout << "Invalid roll number. Must be a positive integer.\n";
                continue;
            }
            if (!h.removeStudent(rollNumber))
                cout << "No records found for roll " << rollNumber << ".\n";
            else
                cout << "All records removed for roll " << rollNumber << ".\n";

        } else if (choice == 6) {
            cout << "Current attendance table:";
            h.display();

        } else if (choice == 7) {
            cout << "Exiting. Goodbye!\n";

        } else {
            cout << "Invalid choice. Please enter a number from 1 to 7.\n";
        }

    } while (choice != 7);

    return 0;
}
