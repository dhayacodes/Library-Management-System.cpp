# Library-Management-System.cpp

## Introduction
The Library Management System is a console-based application developed using C++. The project is designed to manage library operations efficiently, including book addition, issue, return, and search functionalities.

The system uses Object-Oriented Programming (OOP) concepts and file handling techniques to store and manage book records permanently.

---

## Objectives
- To understand Object-Oriented Programming concepts in C++
- To implement file handling for permanent data storage
- To manage library records efficiently
- To perform book issue and return operations

---

## Features
- Add new books
- Display all books
- Issue books
- Return books
- Search books by title
- Search books by author
- Permanent storage using file handling

---

## Technologies Used
- Programming Language: C++
- Concepts Used:
  - Classes and Objects
  - Encapsulation
  - File Handling
  - Functions

---

## OOP Concepts Used

### 1. Class and Object
A `Book` class is used to represent book details and operations.

### 2. Encapsulation
Book data such as book ID, title, author, and issue status are stored as private data members.

### 3. Member Functions
Functions are used to perform operations like add, issue, return, and search.

---

## File Handling
The project uses:
- `ifstream`
- `ofstream`
- `fstream`

Book records are stored in:

```text
library.dat
