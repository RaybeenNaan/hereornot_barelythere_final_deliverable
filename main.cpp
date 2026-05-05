#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int key;
    string value;
    Node *next;

    Node(int k, string v)
    {
        key = k;
        value = v;
        next = nullptr;
    }
};

class HashTable
{
private:
    static const int bucket = 10;
    Node *table[bucket];

public:
    HashTable()
    {
        for (int i = 0; i < bucket; i++)
        {
            table[i] = nullptr;
        }
    }

    int hashFunction(int key)
    {
        return key % 10;
    }

    void markPresent(int rollNumber, string date)
    {
        int index = hashFunction(rollNumber);
        Node *newNode = new Node(rollNumber, date);
        newNode->next = table[index];
        table[index] = newNode;
    }

    int countPresent(int rollNumber)
    {
        int index = hashFunction(rollNumber);
        Node *current = table[index];
        int count = 0;
        while (current != nullptr)
        {
            if (current->key == rollNumber)
                count++;
            current = current->next;
        }
        return count;
    }

    bool wasPresent(int rollNumber, string date)
    {
        int index = hashFunction(rollNumber);
        Node *current = table[index];
        while (current != nullptr)
        {
            if (current->key == rollNumber && current->value == date)
                return true;
            current = current->next;
        }
        return false;
    }

    void removeDay(int rollNumber, string date)
    {
        int index = hashFunction(rollNumber);
        Node *current = table[index];
        Node *prev = nullptr;
        while (current != nullptr)
        {
            if (current->key == rollNumber && current->value == date)
            {
                if (prev == nullptr)
                    table[index] = current->next;
                else
                    prev->next = current->next;
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void removeStudent(int rollNumber)
    {
        int index = hashFunction(rollNumber);
        Node *current = table[index];
        Node *prev = nullptr;
        while (current != nullptr)
        {
            if (current->key == rollNumber)
            {
                Node *toDelete = current;
                if (prev == nullptr)
                {
                    table[index] = current->next;
                    current = table[index];
                }
                else
                {
                    prev->next = current->next;
                    current = current->next;
                }
                delete toDelete;
            }
            else
            {
                prev = current;
                current = current->next;
            }
        }
    }

    void display()
    {
        cout << "\n";
        for (int i = 0; i < bucket; i++)
        {
            cout << "[" << i << "] ";
            Node *current = table[i];
            if (current == nullptr)
            {
                cout << "(empty)\n";
                continue;
            }
            cout << "Roll " << current->key;
            while (current != nullptr)
            {
                cout << " -> " << current->value;
                current = current->next;
            }
            cout << "\n";
        }
    }
};

void printMenu()
{
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

int main()
{
    HashTable h;
    int choice;

    do
    {
        printMenu();
        cin >> choice;

        if (choice == 1)
        {
            int rollNumber;
            string date;
            cout << "Enter roll number: ";
            cin >> rollNumber;
            cout << "Enter date (e.g. 2026-05-01): ";
            cin >> date;
            h.markPresent(rollNumber, date);
            cout << "Attendance marked for roll " << rollNumber << " on " << date << ".\n";
        }
        else if (choice == 2)
        {
            int rollNumber;
            cout << "Enter roll number: ";
            cin >> rollNumber;
            cout << "Roll " << rollNumber << " was present " << h.countPresent(rollNumber) << " day(s).\n";
        }
        else if (choice == 3)
        {
            int rollNumber;
            string date;
            cout << "Enter roll number: ";
            cin >> rollNumber;
            cout << "Enter date (e.g. 2026-05-01): ";
            cin >> date;
            bool result = h.wasPresent(rollNumber, date);
            cout << "Roll " << rollNumber << " was " << (result ? "" : "NOT ") << "present on " << date << ".\n";
        }
        else if (choice == 4)
        {
            int rollNumber;
            string date;
            cout << "Enter roll number: ";
            cin >> rollNumber;
            cout << "Enter date to remove (e.g. 2026-05-01): ";
            cin >> date;
            h.removeDay(rollNumber, date);
            cout << "Removed " << date << " for roll " << rollNumber << " (if it existed).\n";
        }
        else if (choice == 5)
        {
            int rollNumber;
            cout << "Enter roll number: ";
            cin >> rollNumber;
            h.removeStudent(rollNumber);
            cout << "All records removed for roll " << rollNumber << ".\n";
        }
        else if (choice == 6)
        {
            cout << "Current attendance table:";
            h.display();
        }
        else if (choice == 7)
        {
            cout << "Exiting. Goodbye!\n";
        }
        else
        {
            cout << "Invalid choice. Please enter a number from 1 to 7.\n";
        }

    } while (choice != 7);

    return 0;
}
