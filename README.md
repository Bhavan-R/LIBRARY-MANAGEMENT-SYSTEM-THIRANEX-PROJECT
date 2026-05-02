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

<img width="827" height="700" alt="Image" src="https://github.com/user-attachments/assets/1fa2d48d-f1e3-467b-a314-f387a7972c31" />



---

### 2. Add Book

This screen shows the process of adding a new book. It validates ISBN format and ensures no duplicate entries are added to the system.

<img width="798" height="788" alt="Image" src="https://github.com/user-attachments/assets/3044526a-2e3a-464c-a779-9905e86af989" />



---

### 3. Add Member

This section demonstrates registering a new member with proper validation for email, phone number, and member ID.

<img width="810" height="774" alt="Image" src="https://github.com/user-attachments/assets/4be7a883-9b46-4e8a-b3fc-2d28d9610c21" />


---

### 4. Issue Book

This output shows issuing books to a member. It validates borrowing limits and available copies before completing the transaction.

<img width="938" height="880" alt="Image" src="https://github.com/user-attachments/assets/68df5d19-8108-47a5-880d-a8368dfd129f" />


---

### 5. Return Book

This screen shows returning books with support for partial returns. It updates both member records and book inventory.

<img width="948" height="881" alt="Image" src="https://github.com/user-attachments/assets/46b50b4c-10d6-457b-aba3-015210b90a85" />


---

### 6. Search Books

Displays search functionality where users can find books by title or author efficiently.

<img width="820" height="795" alt="Image" src="https://github.com/user-attachments/assets/2d7f05e8-29ae-4b74-97e9-a27999270afb" />


---

### 7. Display All Books

Shows the complete list of books in a structured table format including availability and total copies.

<img width="957" height="801" alt="Image" src="https://github.com/user-attachments/assets/7068d8fd-8176-45c1-b7ed-25d61c5834d7" />


---

### 8. Display Members

Displays all registered members along with their borrowing details and limits.

<img width="962" height="820" alt="Image" src="https://github.com/user-attachments/assets/d9e80a99-c8fa-4e45-ab0f-5d7e41fc6cec" />


---

### 9. Save & Load Data

This output shows file operations where data is saved and loaded, ensuring persistence across program runs.

<img width="823" height="784" alt="Image" src="https://github.com/user-attachments/assets/15862e9c-cb17-47d1-b9ec-a90769066a34" />




<img width="836" height="722" alt="Image" src="https://github.com/user-attachments/assets/a9877b2c-58c9-4f24-b685-8cfddf47d65f" />



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
