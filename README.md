# Library Management System

## Overview

The Library Management System is a console-based application developed in C++ that simulates real-world library operations. It manages books, members, and transactions efficiently using Object-Oriented Programming (OOP) principles and file handling for persistent storage.

The system ensures accurate tracking of book inventory, member activities, and borrowing processes with proper validation and structured data management.

---

## Problem Statement

Traditional manual library systems often face issues like duplicate records, incorrect tracking of books, and inefficient member handling. This project addresses these challenges by providing a digital system that ensures:

* Accurate inventory management
* Controlled borrowing system
* Reliable data storage
* Error-free input handling

---

## Objectives

* Implement a real-world system using C++
* Apply OOP concepts (Encapsulation, Abstraction)
* Use file handling for persistent storage
* Ensure strong data validation
* Build a scalable and modular system

---

## Key Features

### Book Management

* Add books with strict ISBN validation (ISBN-10 & ISBN-13)
* Prevent duplicate ISBN entries
* Track total and available copies
* Soft delete books only if no active borrowings

### Member Management

* Register members with validation
* Email and phone validation
* Borrowing limit per member
* Prevent deletion if books are not returned

### Issue Book System

* Issue multiple copies of a book
* Validate member eligibility
* Check availability before issuing
* Prevent exceeding borrowing limits

### Return Book System

* Return partial or full copies
* Update inventory dynamically
* Maintain correct borrowing records

### Search & Display

* Search books by title or author
* Display all books in tabular format
* View all members and their borrowing status

### Data Persistence

* Save data in `books.txt` and `members.txt`
* Load data automatically on startup
* Maintain data consistency across sessions

---

## System Design

### Classes Used

* **Book Class** → Stores book details and availability
* **Member Class** → Manages member information and borrowed books
* **Library Class** → Core logic and operations

### Core Concepts

* Encapsulation of data
* Modular design
* Dynamic storage using STL vectors

---

## Data Structures Used

* Vector → Dynamic storage
* String → Text handling
* StringStream → File parsing
* File Streams → Data persistence

---

## Input Validation

* ISBN checksum validation (10 & 13)
* Email format validation
* Phone number (10 digits)
* Member ID constraints
* Exception handling for invalid input

---

## Algorithm Flow

### Issue Book

1. Validate Member ID
2. Check eligibility
3. Validate ISBN
4. Check availability
5. Issue copies
6. Update records

### Return Book

1. Validate Member
2. Validate ISBN
3. Check borrowed copies
4. Return selected copies
5. Update inventory

---

## How to Run

```bash
g++ main.cpp -o library
./library
```

---

## Output Screenshots

### 1. Main Menu

This screen displays the primary interface of the system. It provides all available operations such as adding books, issuing books, returning books, searching, and saving data.

<img width="827" height="700" alt="image" src="https://github.com/user-attachments/assets/e0ab4159-8061-40d6-bded-29c82675a43c" />


---

### 2. Add Book

This screen shows the process of adding a new book. It validates ISBN format and ensures no duplicate entries are added to the system.

<img width="798" height="788" alt="image" src="https://github.com/user-attachments/assets/a651d1be-a643-4219-bc78-40c8232921dd" />


---

### 3. Add Member

This section demonstrates registering a new member with proper validation for email, phone number, and member ID.

<img width="810" height="774" alt="image" src="https://github.com/user-attachments/assets/41ee0bc2-c19c-4b40-a3ed-c7224c45d9dc" />

---

### 4. Issue Book

This output shows issuing books to a member. It validates borrowing limits and available copies before completing the transaction.

<img width="938" height="880" alt="image" src="https://github.com/user-attachments/assets/a162cbf4-0f49-4b0e-afdf-53fd9a84b8ed" />

---

### 5. Return Book

This screen shows returning books with support for partial returns. It updates both member records and book inventory.

<img width="948" height="881" alt="image" src="https://github.com/user-attachments/assets/fac6aada-3d75-4b50-81d6-f7086c84b549" />

---

### 6. Search Books

Displays search functionality where users can find books by title or author efficiently.

<img width="820" height="795" alt="image" src="https://github.com/user-attachments/assets/fadd5a30-e220-4b02-955f-c6161ca59fd5" />

---

### 7. Display All Books

Shows the complete list of books in a structured table format including availability and total copies.

<img width="965" height="811" alt="image" src="https://github.com/user-attachments/assets/0bb0143a-7183-487b-9594-bc3aed3707bc" />

---

### 8. Display Members

Displays all registered members along with their borrowing details and limits.

<img width="962" height="820" alt="image" src="https://github.com/user-attachments/assets/532ba1f5-c816-4732-9d7a-e0aedc397493" />

---

### 9. Save & Load Data

This output shows file operations where data is saved and loaded, ensuring persistence across program runs.

<img width="823" height="784" alt="image" src="https://github.com/user-attachments/assets/aaf7598e-32b3-4e42-86fc-3eb7d0241719" />



<img width="836" height="722" alt="image" src="https://github.com/user-attachments/assets/3d874c4d-1c5b-4975-82f0-6020030e71c9" />


---

## Advantages

* Clean and modular design
* Strong validation ensures data accuracy
* Real-time inventory tracking
* Persistent storage without database
* Easy to understand and extend

---

## Limitations

* Console-based interface
* Linear search (less efficient for large data)
* No authentication system
* No database integration

---

## Future Enhancements

* GUI using Qt or Web technologies
* Database integration (MySQL/SQLite)
* User authentication system
* Fine calculation for late returns
* Barcode/QR code integration

---

## Learning Outcomes

* Practical use of OOP in C++
* File handling and persistence
* Data validation techniques
* Real-world system design
* Debugging and problem solving

---

## Conclusion

This project successfully implements a Library Management System using C++. It demonstrates efficient handling of data, proper validation, and structured design using OOP principles. The system is scalable and can be further enhanced with modern technologies.

---
