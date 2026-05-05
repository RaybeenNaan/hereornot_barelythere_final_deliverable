[ATTENDENCE TRACKER]

- **Authors:** Sulab Karki, Syed afnan Iftikhar, Samaya Tiwari
- **Course:** CSC 307 H002-H003
- **Semester:** SPRING 2026

---

## 1. Prerequisites & Environment

Before running this project, ensure your system meets the following requirements:

- **Operating System:** Windows 10/11, Ubuntu 22.04+, or macOS (any recent version)
- **Compiler:** GCC/g++ 9.0+ (MinGW on Windows), Clang 12+, or MSVC 2019+
- **Build System:** any IDE

---

### Required Libraries

List any external frameworks used:

- `<iostream>` â€” Console input/output
- `<fstream>` â€” File reading and writing for record persistence
- `<string>` â€” String handling for dates and parsing

---

## 2. Installation & Setup

No external libraries or installations are required beyond a working C++ compiler.

1. Install a C++ compiler if you do not already have one:
   - **Windows:** Install [MinGW-w64] and add the `bin` folder to your `PATH`, **or** install MSYS2.
   - **Ubuntu/Debian:** `sudo apt install g++`
   - **macOS:** Install Xcode Command Line Tools: `xcode-select --install`
2. Download or clone the project source file (`main.cpp`) into a folder of your choice.

---

## 3. Build Instructions

**Using Command Line (Windows / Linux / macOS):**

```bash
g++ main.cpp -o attendance
```

This produces an executable file named `attendance` (or `attendance.exe` on Windows) in the same folder as `main.cpp`.

**Using an IDE:**

- **VS Code:** Open the folder, then run the C++ build task (default shortcut `Ctrl+Shift+B`).

---

## 4. Execution Guide

Once built, the program is run from a terminal or directly through the IDE.

- **Executable Name:** `attendance` (Linux/macOS) or `attendance.exe` (Windows)
- **Entry Point:** No command-line arguments are required. Run with:

  ```bash
  ./attendance
  ```

- **Data File:** When the program runs, it reads from and writes to a file named `attendence.txt` located in the **current working directory** (the folder the executable was launched from). On the first run this file does not exist yet â€” it is created automatically the first time attendance is marked. On subsequent runs, all previous records are loaded from this file at startup.

- **Menu Options:**
  1. **Mark attendance** â€” Enter a date, then enter roll numbers one at a time. Type `stop` (lowercase) to finish.
  2. **View attendance for a roll number** â€” Look up all dates a specific student attended.
  3. **View all records** â€” Display every student in every bucket of the hash table.
  4. **Edit a date for a student** â€” Replace one of a student's existing dates with a new one.
  5. **Delete a date for a student** â€” Remove a single date from a student's record.
  6. **Exit** â€” Closes the program. All data is already saved.

- **Sample Workflow:**

  ```
  Select taske: 1
  Enter date for today's attendance: January 5
  Enter rollnumber (or 'stop' to finish): 1021527
  Enter rollnumber (or 'stop' to finish): 1021888
  Enter rollnumber (or 'stop' to finish): stop
  ```

---

## 5. Troubleshooting / Known Issues

- **`attendence.txt` not appearing where expected:** When run from an IDE, the working directory is often the IDE's project/build folder rather than the folder containing `main.cpp`. Search your project folder recursively for `attendence.txt` to locate it, or run the executable directly from a terminal.
- **The `stop` keyword is case-sensitive:** During attendance marking, only lowercase `stop` will end the input loop. `Stop` or `STOP` will be treated as invalid roll numbers.
- **Roll numbers must be positive integers:** Any input that contains letters, symbols, or is zero/negative will be rejected with an error message and the program will prompt again. The program will not crash.
- **Hash table size is fixed at 10 buckets:** Defined by the constant `tablesize` near the top of the source file. Multiple students whose roll numbers share the same `% 10` result are chained together using a linked list (separate chaining collision handling). To change the table size, edit the `tablesize` constant and recompile.
- **Data file format:** `attendence.txt` stores one record per line in the format `rollnumber,date`. The file can be viewed or edited manually with any text editor, but malformed lines will be silently skipped when loading.
