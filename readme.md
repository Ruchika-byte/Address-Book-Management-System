# Address Book Application (C)

A terminal-based **Address Book management system** written in C, built and run using **Visual Studio Code (VS Code)** on Windows. 

This application offers an interactive terminal menu to track your contacts and automatically serializes the data to a comma-separated file.

##  Key Features & Validation Logic
* **Persistent CSV Storage:** Automatically reads from and writes current records to a `contact.csv`  database file.
* **Name Validation:** Restricts contact names from containing digits or special symbols.
* **TRAI-Compliant Phone Handling:** Restricts mobile numbers strictly to a 10-digit limit and verifies they begin with valid national prefixes ('6', '7', '8', or '9').Restricts user from entering special symbols or letters.Also verifies duplicate entry
* **Email Rule Assessment:** Validates placements for `@` and `.com`, while blocking duplicate values across entries.

##  Project Directory Structure

Ruchika_addressbook/
├── main.c             # Menu loop and runtime selection switch
├── contact.c          # CRUD operations, trimming, and validation rules
├── contact.h          # Global declarations, structs, prototypes
├── populate.c         # Preloaded sample contacts (initialize)
├── contact.csv        # Storage file (comma-separated)
└── README.md          # Documentation


## Setup Prerequisites
1. **Extensions:** Install the official **C/C++ extension** by Microsoft in VS Code.
2. **Compiler:** Use **WSL (Ubuntu)** with GCC installed (`sudo apt install gcc`).

## How to Compile
Open a **WSL (Ubuntu)** terminal in VS Code, go to the project folder and run:

    gcc *.c

## How to Run

    ./a.out


##  Main Menu Configuration Map
The program loops your CLI options via numeric selections directly inside your output console windows:

Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save and Exit
Enter your choice: 
When the choice is 6, the program saves all newly created, updated or deleted contacts to the `contact.csv` file.
