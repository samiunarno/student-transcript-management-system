# Student Transcript Management System (C Language)

## 📌 Project Overview
This project is a **Student Transcript Management System** developed in **C**. It uses a **singly linked list** as the core data structure to dynamically organize, manage, and process student records in memory. The system is designed to read from and save to text files, allowing for persistent data storage across sessions. 

This project is an extended implementation based on *Example 11.1: Using Files to Save Transcript Data* from the textbook *Fundamentals of Programming (3rd Edition, Chen Juan, Zhang Changhai)*.

## ⚙️ System Architecture

The application is built with a modular, menu-driven architecture to ensure robust and user-friendly CLI operations.

```text
+---------------------+
|     User (CLI)      |
+----------+----------+
           |
           v
+---------------------+
|   Login Module      |  <-- Validates user credentials (users.txt)
| (validateUser)      |
+----------+----------+
           |
           v
+---------------------+
|   Main Menu System  |  <-- Routes commands to core operations
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
| Linked List Storage |  <-- Dynamic memory management (Singly Linked List)
| (Student Nodes)     |
+----------+----------+
           |
           v
+---------------------+
| File System (Disk)  |  <-- Persistent storage
| transcripts.txt     |
+---------------------+