[Here Or Not]
Author: [Syed Afnan Iftikhar, Sulab Karki]

Course: [CSC 307]

Semester: [Spring 2026]
---

1. Prerequisites & Environment
Before running this project, ensure your system meets the following requirements:

Operating System: Windows 10/11, macOS, or Linux (Ubuntu/Debian recommended)

Compiler: GCC (g++) 9.0+, Clang, or MSVC (Visual Studio 2019+)

Standard: C++11 or higher (required for nullptr and modern string handling)

Required Libraries

This project is built using the C++ Standard Library, making it highly portable with no external dependencies required:

iostream: Handles console input (cin) and output (cout).

string: Manages student date records and names.
---

2. Installation & Setup
Since this is a header-less single-file implementation, setup is straightforward:

Download the Source: Save the code provided as AttendanceSystem.cpp.

Terminal Access: Open your terminal (Command Prompt, PowerShell, or Bash).

Directory: Navigate to the folder where you saved the file.
---

3. Build Instructions
How do I compile the source code?

Using Command Line (Recommended): ```bash
g++ -o HereOrNot AttendanceSystem.cpp


**Using Visual Studio:** * Create a new **C++ Empty Project**.
* Add a new item `main.cpp` and paste the code.
* Press **F5** to compile and run.

---

## 4. Execution Guide 
The program uses a hash table with **Chaining (Linked Lists)** to handle attendance records.

* **Executable Name:** `HereOrNot` (or `HereOrNot.exe` on Windows).
* **Data Structure:** The system uses a **Hash Table** with 10 buckets. Each bucket contains a linked list of `Node` objects.
* **Functionality:**
    1. **Mark Present:** Hashes the Roll Number and adds a new node to the head of the corresponding bucket's list.
    2. **Count Days:** Traverses the specific bucket list to count occurrences of a Roll Number.
    3. **Remove Student:** Deletes all linked nodes associated with a specific Roll Number.



---

## 5. Troubleshooting / Known Issues 
* **Hash Collisions:** The current `bucket` size is set to 10. For a very large student body, this may lead to longer linked lists in each bucket, slightly slowing down performance.
* **Input Validation:** The program expects `int` for choices and roll numbers. Entering a string when an integer is expected may cause an infinite loop in the menu.
* **Case Sensitivity:** Dates are stored as strings; searching for "2026-may-01" will not match "2026-May-01".

---

## 6. Project Logic Summary
The core of **[Here Or Not]** is the `HashTable` class:
* **Hash Function:** Uses the modulo operator ($key \pmod{10}$) to determine the index.
* **Memory Management:** The `removeStudent` and `removeDay` methods explicitly use the `delete` keyword to prevent memory leaks, ensuring that each node removed from the linked list is properly freed from the heap.
