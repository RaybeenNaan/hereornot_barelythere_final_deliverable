#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct DateNode
{
  string date;
  DateNode *next;
};

struct StudentNode
{
  int rollnumber;         // the student's roll number
  DateNode *datelisthead; // pointer to the first date a student attended
  StudentNode *next;      // pointer to the next student in this bucket
};

const int tablesize = 10;                  // sie of hash table
const string file_name = "attendence.txt"; // file to save the attendence record

class attendenceHashTable
{
private:
  StudentNode *bucket[tablesize];

  int getbucketindex(int rollnumber)
  { // hashFuntion
    return rollnumber % tablesize;
  }

  StudentNode *findStudent(int rollnumber)
  { // search for a student using key rollnumber, return node or nullpointer
    int index = getbucketindex(rollnumber);
    StudentNode *current = bucket[index];

    while (current != nullptr)
    {
      if (current->rollnumber == rollnumber)
      {
        return current;
      }
      current = current->next;
    }
    return nullptr;
  }
  void addDate(int rollnumber, string date) // adds a date for a roll number
  {
    StudentNode *student = findStudent(rollnumber);
    if (student == nullptr)
    {
      student = new StudentNode; // if student doesn't exist, create one
      student->rollnumber = rollnumber;
      student->datelisthead = nullptr; // first node has poitners on null
      student->next = nullptr;         // first node has poitners on null

      int index = getbucketindex(rollnumber);
      if (bucket[index] == nullptr)
      {
        bucket[index] = student;
      }
      else
      {
        StudentNode *tailStudent = bucket[index]; // if bucket isnt empty, treverse linked list to last chain
        while (tailStudent->next != nullptr)
        {
          tailStudent = tailStudent->next;
        }
        tailStudent->next = student; // attach new student to end
      }
    }
    DateNode *newDate = new DateNode; // create a new date node
    newDate->date = date;
    newDate->next = nullptr;

    if (student->datelisthead == nullptr) // if student has no dates yet
    {
      student->datelisthead = newDate;
    }
    else
    {
      DateNode *lastDate = student->datelisthead;
      while (lastDate->next != nullptr)
      {
        lastDate = lastDate->next;
      }
      lastDate->next = newDate;
    }
  }

public:
  attendenceHashTable() // constructor
  {
    for (int i = 0; i < tablesize; i++)
    {
      bucket[i] = nullptr;
    }
  }

  ~attendenceHashTable()
  {
    for (int i = 0; i < tablesize; i++)
    {
      StudentNode *current = bucket[i];
      while (current != nullptr)
      {
        DateNode *currentDate = current->datelisthead;
        while (currentDate != nullptr)
        {
          DateNode *tempDate = currentDate;
          currentDate = currentDate->next;
          delete tempDate;
        }
        StudentNode *tempStudent = current;
        current = current->next;
        delete tempStudent;
      }
    }
  }

  void savetofile()
  {
    ofstream outFile(file_name);
    if (!outFile.is_open())
    {
      cout << "Could not open file" << endl;
      return;
    }

    for (int i = 0; i < tablesize; i++)
    {
      StudentNode *current = bucket[i];
      while (current != nullptr)
      {
        DateNode *currentDate = current->datelisthead;
        while (currentDate != nullptr)
        {
          outFile << current->rollnumber << "," << currentDate->date << endl;
          currentDate = currentDate->next;
        }
        current = current->next;
      }
    }
    outFile.close();
  }

  void makePresent(int rollnumber, string date)
  {
    addDate(rollnumber, date);
    savetofile();
  }

  void showAttendance(int rollNumber) // show all dates a specific student was present
  {
    StudentNode *student = findStudent(rollNumber);

    if (student == nullptr)
    {
      cout << "No attendance recorded yet." << endl;
      return;
    }

    cout << "Roll Number " << student->rollnumber << " was present on: ";
    DateNode *current = student->datelisthead;
    while (current != nullptr)
    {
      cout << current->date;
      if (current->next != nullptr)
      {
        cout << " -> ";
      }
      current = current->next;
    }
    cout << endl;
  }

  void showAllRecords()
  {
    bool found = false;
    for (int i = 0; i < tablesize; i++)
    {
      if (bucket[i] != nullptr)
      {
        found = true;
        cout << "Bucket " << i << ":" << endl;
        StudentNode *current = bucket[i];
        while (current != nullptr)
        {
          cout << "  Roll " << current->rollnumber << " -> ";
          DateNode *currentDate = current->datelisthead;
          while (currentDate != nullptr)
          {
            cout << currentDate->date;
            if (currentDate->next != nullptr)
            {
              cout << " -> ";
            }
            currentDate = currentDate->next;
          }
          cout << endl;
          current = current->next;
        }
      }
    }
    if (!found)
    {
      cout << "No records yet." << endl;
    }
  }

  bool updateDate(int rollnumber, string oldDate, string newDate)
  {
    StudentNode *student = findStudent(rollnumber);
    if (student == nullptr)
    {
      return false;
    }

    DateNode *current = student->datelisthead;
    while (current != nullptr)
    {
      if (current->date == oldDate)
      {
        current->date = newDate;
        savetofile();
        return true;
      }
      current = current->next;
    }
    return false;
  }

  bool deleteDate(int rollnumber, string date)
  {
    StudentNode *student = findStudent(rollnumber);
    if (student == nullptr)
    {
      return false;
    }

    DateNode *current = student->datelisthead;
    DateNode *previous = nullptr;

    while (current != nullptr)
    {
      if (current->date == date)
      {
        if (previous == nullptr)
        {
          student->datelisthead = current->next;
        }
        else
        {
          previous->next = current->next;
        }
        delete current;
        savetofile();
        return true;
      }
      previous = current;
      current = current->next;
    }
    return false;
  }

  void loadFromFile() // read attendance data from file
  {
    ifstream inFile(file_name);
    if (!inFile.is_open())
    {
      return;
    }

    string line;
    while (getline(inFile, line))
    {
      size_t commaPosition = line.find(','); // find where the comma is in "rollnumber,date"
      if (commaPosition == string::npos)     // skip line if no comma found
        continue;

      string rollnumberString = line.substr(0, commaPosition); // get text before comma
      string date = line.substr(commaPosition + 1);            // get text after comma
      try
      {
        int rollNumber = stoi(rollnumberString);
        if (rollNumber > 0)
        {
          addDate(rollNumber, date);
        }
      }
      catch (...)
      {
        continue;
      }
    }
    inFile.close();
  }
};

bool tryReadRollNumber(const string &input, int &result)
{
  if (input.empty())
  {
    return false;
  }
  try
  {
    size_t processed;
    result = stoi(input, &processed);
    if (processed != input.length())
    {
      return false;
    }
    if (result <= 0)
    {
      return false;
    }
    return true;
  }
  catch (...)
  {
    return false;
  }
}

void showMenu()
{
  cout << endl;
  cout << "[ AtTTENDENCE TRACKER ]" << endl;
  cout << "1. Mark attendence" << endl;
  cout << "2. View attendance for a roll number" << endl;
  cout << "3. View all records" << endl;
  cout << "4. Edit a date for a student" << endl;
  cout << "5. Delete a date for a student" << endl;
  cout << "6. Exit" << endl;
  cout << "---------------------------------------" << endl;
  cout << "Select taske: ";
}

int main()
{
  attendenceHashTable csc307;
  csc307.loadFromFile();

  int choice;
  while (true)
  {
    showMenu();

    if (!(cin >> choice))
    {
      cout << "Please enter a number between 1 and 6" << endl;
      cin.clear();
      cin.ignore(10000, '\n'); // ignore the invalid input
      continue;
    }
    cin.ignore(10000, '\n');

    if (choice == 1)
    {
      string date;
      cout << "Enter date for today's attendance: ";
      getline(cin, date);
      cout << "Now enter present rollnumbers. Type 'stop' when done." << endl;

      string input;
      while (true)
      {
        cout << "Enter rollnumber (or 'stop' to finish): ";
        getline(cin, input);

        if (input == "stop")
        {
          cout << "All attendance have been saved to " << file_name << "." << endl;
          break;
        }

        if (input.empty())
        {
          cout << "Empty input, please try again." << endl;
          continue;
        }

        int rollnumber;
        if (!tryReadRollNumber(input, rollnumber))
        {
          cout << "Invalid roll number. Must be a positive integer." << endl;
          continue;
        }
        csc307.makePresent(rollnumber, date);
        cout << "Roll " << rollnumber << " marked present on " << date << "." << endl;
      }
    }
    else if (choice == 2)
    {
      string input;
      cout << "Enter Roll Number: ";
      getline(cin, input);

      int rollnumber;
      if (!tryReadRollNumber(input, rollnumber))
      {
        cout << "Invalid roll number. Must be a positive integer." << endl;
        continue;
      }

      csc307.showAttendance(rollnumber);
    }
    else if (choice == 3)
    {
      csc307.showAllRecords();
    }
    else if (choice == 4)
    {
      string input;
      cout << "Enter Roll Number: ";
      getline(cin, input);

      int rollnumber;
      if (!tryReadRollNumber(input, rollnumber))
      {
        cout << "Invalid roll number. Must be a positive integer." << endl;
        continue;
      }

      csc307.showAttendance(rollnumber);

      string oldDate;
      cout << "Enter the date you want to change: ";
      getline(cin, oldDate);
      if (oldDate.empty())
      {
        cout << "Date cannot be empty." << endl;
        continue;
      }

      string newDate;
      cout << "Enter the new date: ";
      getline(cin, newDate);
      if (newDate.empty())
      {
        cout << "Date cannot be empty." << endl;
        continue;
      }

      if (csc307.updateDate(rollnumber, oldDate, newDate))
      {
        cout << "Date updated. " << oldDate << " is now " << newDate << "." << endl;
      }
      else
      {
        cout << "Roll number or date not found." << endl;
      }
    }
    else if (choice == 5)
    {
      string input;
      cout << "Enter Roll Number: ";
      getline(cin, input);

      int rollnumber;
      if (!tryReadRollNumber(input, rollnumber))
      {
        cout << "Invalid roll number. Must be a positive integer." << endl;
        continue;
      }

      csc307.showAttendance(rollnumber);

      string date;
      cout << "Enter the date to delete: ";
      getline(cin, date);
      if (date.empty())
      {
        cout << "Date cannot be empty." << endl;
        continue;
      }

      if (csc307.deleteDate(rollnumber, date))
      {
        cout << "Date " << date << " removed from roll " << rollnumber << "." << endl;
      }
      else
      {
        cout << "Roll number or date not found." << endl;
      }
    }

    else if (choice == 6)
    {
      cout << "Goodbye!" << endl;
      break;
    }
    else
    {
      cout << "Please try again." << endl;
    }
  }
  return 0;
}
