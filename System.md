+---------------------+
|     User (CLI)      |
+----------+----------+
           |
           v
+---------------------+
|   Login Module      |
| (validateUser)      |
+----------+----------+
           |
           v
+---------------------+
|   Main Menu System  |
| (menu function)     |
+----------+----------+
           |
   -------------------------
   |     |      |     |     |
   v     v      v     v     v
 Load  Add   Delete Search Sort
 File Student Student  Data  Data
   |     |      |     |     |
   -------------------------
           |
           v
+---------------------+
| Linked List Storage |
| (Student Nodes)     |
+----------+----------+
           |
           v
+---------------------+
| File System (Disk)  |
| students.txt        |
| users.txt           |
+---------------------+

Module Breakdown
🔐 1. Login Module

Function: validateUser()

Input: username, password

Source: users.txt

Output: Access granted / denied

📋 2. Menu Module

Function: menu()

Controls all system operations

Acts as controller layer

📂 3. File Handling Module
Input:

loadFromFile()

Reads students.txt

Creates linked list

Output:

saveToFile()

Writes updated data back to file

🔗 4. Data Structure Layer
Singly Linked List:

Each node contains:

ID

Name

5 subject scores

Total

Pointer → next node

👉 Dynamic memory (malloc) used

⚙️ 5. Processing Module
Operations:

➕ addStudent()

❌ deleteStudent()

🔍 searchStudent()

📊 sortByTotal()

👉 All operations manipulate linked list (RAM)

💾 6. Data Persistence Layer

File: students.txt

Stores:

ID Name score1 score2 score3 score4 score5

👉 Ensures data is saved permanently

🔄 Data Flow
Disk File → loadFromFile() → Linked List (RAM)
Linked List → عملیات (Add/Delete/Search)
Linked List → saveToFile() → Disk File
🧠 Key Design Concepts

Separation of concerns

Login, Data, UI, Storage 

Dynamic memory allocation

Persistent storage via file

Menu-driven interaction

Linked list instead of array

🧾 Short Description (for report)

You can write this:

The system follows a modular architecture consisting of a login module, menu-driven control system, linked list-based data management layer, and file-based storage system. User authentication is handled through a credential file. Student records are dynamically managed using a singly linked list in memory, while persistent storage is maintained through file operations. All CRUD operations are performed on the linked list and synchronized with the file system.