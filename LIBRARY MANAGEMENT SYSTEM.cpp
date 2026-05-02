#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cctype>

using namespace std;

class Book {
private:
    string isbn;
    string title;
    string author;
    string genre;
    int totalCopies;
    int availableCopies;
    bool isDeleted;

public:
    Book() : isbn(""), title(""), author(""), genre(""), totalCopies(0), availableCopies(0), isDeleted(false) {}
    
    Book(string isbn, string title, string author, string genre, int copies) 
        : isbn(isbn), title(title), author(author), genre(genre), totalCopies(copies), 
          availableCopies(copies), isDeleted(false) {}

    string getISBN() const { return isbn; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getGenre() const { return genre; }
    int getTotalCopies() const { return totalCopies; }
    int getAvailableCopies() const { return availableCopies; }
    bool getIsDeleted() const { return isDeleted; }

    void setAvailableCopies(int copies) {
        if (copies >= 0 && copies <= totalCopies) {
            availableCopies = copies;
        }
    }

    void setDeleted(bool status) { isDeleted = status; }

    bool isAvailable() const { return availableCopies > 0 && !isDeleted; }

    string toString() const {
        stringstream ss;
        ss << left << setw(15) << isbn << setw(25) << title << setw(20) << author 
           << setw(12) << genre << setw(8) << totalCopies << setw(8) << availableCopies;
        return ss.str();
    }
};

class Member {
private:
    string memberId;
    string name;
    string email;
    string phone;
    int maxBooks;
    vector<string> borrowedBooks;
    bool isActive;
    bool isDeleted;

public:
    Member() : memberId(""), name(""), email(""), phone(""), maxBooks(3), isActive(false), isDeleted(false) {}
    
    Member(string id, string name, string email, string phone, int maxBooks = 3)
        : memberId(id), name(name), email(email), phone(phone), maxBooks(maxBooks), 
          isActive(true), isDeleted(false) {}

    string getMemberId() const { return memberId; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getPhone() const { return phone; }
    int getMaxBooks() const { return maxBooks; }
    vector<string> getBorrowedBooks() const { return borrowedBooks; }
    bool getIsActive() const { return isActive; }
    bool getIsDeleted() const { return isDeleted; }

    void setActive(bool status) { isActive = status; }
    void setDeleted(bool status) { isDeleted = status; }

    bool canBorrow() const {
        return isActive && !isDeleted && borrowedBooks.size() < maxBooks;
    }

    int getBorrowedCopies(const string& isbn) const {
        int count = 0;
        for (const string& book : borrowedBooks) {
            if (book == isbn) count++;
        }
        return count;
    }

    bool hasBorrowedBook(const string& isbn) const {
        return getBorrowedCopies(isbn) > 0;
    }

    void addBorrowedBook(const string& isbn) {
        borrowedBooks.push_back(isbn);  
    }

    bool returnBook(const string& isbn, int copiesToReturn) {
        int removed = 0;
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end() && removed < copiesToReturn; ) {
            if (*it == isbn) {
                it = borrowedBooks.erase(it);
                ++removed;
            } else {
                ++it;
            }
        }
        return removed == copiesToReturn;
    }

    string toString() const {
        stringstream ss;
        ss << left << setw(12) << memberId << setw(20) << name << setw(25) << email 
           << setw(15) << phone << setw(8) << borrowedBooks.size() << "/" << maxBooks;
        return ss.str();
    }
};

bool isValidISBN10(const string& isbn) {
    string clean;
    for (char c : isbn) {
        if (isdigit(c) || (c == 'X' || c == 'x')) clean += toupper(c);
        else if (c != '-') continue;
    }
    
    if (clean.length() != 10) return false;
    
    int sum = 0;
    for (int i = 0; i < 9; i++) {
        sum += (clean[i] - '0') * (10 - i);
    }
    char check = clean[9];
    int checkDigit = (check == 'X') ? 10 : (check - '0');
    
    return (sum + checkDigit) % 11 == 0;
}

bool isValidISBN13(const string& isbn) {
    string clean;
    for (char c : isbn) {
        if (isdigit(c)) clean += c;
        else if (c != '-') continue;
    }
    
    if (clean.length() != 13) return false;
    
    int sum = 0;
    for (int i = 0; i < 13; i++) {
        int digit = clean[i] - '0';
        sum += (i % 2 == 0) ? digit : digit * 3;
    }
    
    return sum % 10 == 0;
}

bool isValidISBN(const string& isbn) {
    return isValidISBN10(isbn) || isValidISBN13(isbn);
}

class Library {
private:
    vector<Book> books;
    vector<Member> members;
    string libraryName;

    bool getValidISBN(string& isbn) {
        int attempts = 0;
        while (true) {
            if (attempts == 0) {
                cout << "Enter ISBN: ";
            } else {
                cout << "Invalid ISBN! ";
            }
            attempts++;
            getline(cin >> ws, isbn);
            
            if (isValidISBN(isbn)) return true;
            
            if (attempts == 1) {
                cout << "Examples - ISBN-10: 0-306-40615-2, ISBN-13: 978-0-306-40615-7\n";
            }
            cout << "Please try again.\n";
        }
    }

    bool getValidMemberId(string& id) {
        int attempts = 0;
        while (true) {
            if (attempts == 0) {
                cout << "Enter Member ID: ";
            } else {
                cout << "Invalid Member ID! ";
            }
            attempts++;
            getline(cin >> ws, id);
            
            if (!id.empty() && id.length() <= 10 && id.find(' ') == string::npos) {
                return true;
            }
            
            if (attempts == 1) {
                cout << "Examples: M001, STUDENT123 (1-10 chars, no spaces)\n";
            }
            cout << "Please try again.\n";
        }
    }

    bool getValidEmail(string& email) {
        int attempts = 0;
        while (true) {
            if (attempts == 0) {
                cout << "Enter Email: ";
            } else {
                cout << "Invalid email! ";
            }
            attempts++;
            getline(cin, email);
            
            size_t atPos = email.find('@');
            size_t dotPos = email.find('.', atPos + 1);
            if (atPos != string::npos && dotPos != string::npos && !email.empty()) {
                return true;
            }
            
            if (attempts == 1) {
                cout << "Example: john@example.com (must contain @ and .)\n";
            }
            cout << "Please try again.\n";
        }
    }

    bool getValidPhone(string& phone) {
        int attempts = 0;
        while (true) {
            if (attempts == 0) {
                cout << "Enter Phone Number: ";
            } else {
                cout << "Invalid phone! ";
            }
            attempts++;
            getline(cin, phone);
            
            if (phone.length() == 10) {
                bool valid = true;
                for (char c : phone) {
                    if (!isdigit(c)) {
                        valid = false;
                        break;
                    }
                }
                if (valid) return true;
            }
            
            if (attempts == 1) {
                cout << "Example: 9876543210 (exactly 10 digits)\n";
            }
            cout << "Please try again.\n";
        }
    }

    bool getValidCopies(int& copies) {
        int attempts = 0;
        while (true) {
            if (attempts == 0) {
                cout << "Enter Quantity/Copies: ";
            } else {
                cout << "Invalid quantity! ";
            }
            attempts++;
            string input;
            getline(cin >> ws, input);
            
            try {
                copies = stoi(input);
                if (copies >= 1 && copies <= 1000) return true;
                if (attempts == 1) {
                    cout << "Must be between 1-1000\n";
                }
            } catch (...) {
                if (attempts == 1) {
                    cout << "Please enter valid number (1-1000)\n";
                }
            }
            cout << "Please try again.\n";
        }
    }

    bool getValidMaxBooks(int& maxBooks) {
        int attempts = 0;
        while (true) {
            if (attempts == 0) {
                cout << "Enter Max Books Allowed (1-10, Enter for 3): ";
            } else {
                cout << "Invalid number! ";
            }
            attempts++;
            string input;
            getline(cin >> ws, input);
            
            if (input.empty() || input == "3") {
                maxBooks = 3;
                return true;
            }
            
            try {
                maxBooks = stoi(input);
                if (maxBooks >= 1 && maxBooks <= 10) return true;
                if (attempts == 1) {
                    cout << "Must be between 1-10\n";
                }
            } catch (...) {
                if (attempts == 1) {
                    cout << "Please enter valid number (1-10)\n";
                }
            }
            cout << "Please try again.\n";
        }
    }

    bool getNonEmptyString(string& str, const string& fieldName) {
        int attempts = 0;
        while (true) {
            if (attempts == 0) {
                cout << "Enter " << fieldName << ": ";
            } else {
                cout << fieldName << " cannot be empty! ";
            }
            attempts++;
            getline(cin, str);
            if (!str.empty()) return true;
            cout << "Please try again.\n";
        }
    }

    bool isDuplicateISBN(const string& isbn) const {
        for (const auto& book : books) {
            if (book.getISBN() == isbn && !book.getIsDeleted()) return true;
        }
        return false;
    }

    bool isDuplicateMemberId(const string& id) const {
        for (const auto& member : members) {
            if (member.getMemberId() == id && !member.getIsDeleted()) return true;
        }
        return false;
    }

public:
    Library(string name) : libraryName(name) {}

    void addBook() {
        cout << "\n=== ADD NEW BOOK ===\n";
        
        string isbn, title, author, genre;
        int copies;

        if (!getValidISBN(isbn)) return;
        if (isDuplicateISBN(isbn)) {
            cout << "Book with ISBN '" << isbn << "' already exists! Cannot add duplicate.\n";
            return;
        }

        if (!getNonEmptyString(title, "Title")) return;
        if (!getNonEmptyString(author, "Author")) return;
        if (!getNonEmptyString(genre, "Genre")) return;
        if (!getValidCopies(copies)) return;

        books.emplace_back(isbn, title, author, genre, copies);
        cout << "\nBook '" << title << "' added successfully with " << copies << " copies!\n";
    }

    void addMember() {
        cout << "\n=== ADD NEW MEMBER ===\n";
        
        string id, name, email, phone;
        int maxBooks;

        if (!getValidMemberId(id)) return;
        if (isDuplicateMemberId(id)) {
            cout << "Member ID '" << id << "' already exists! Cannot add duplicate.\n";
            return;
        }

        if (!getNonEmptyString(name, "Name")) return;
        if (!getValidEmail(email)) return;
        if (!getValidPhone(phone)) return;
        if (!getValidMaxBooks(maxBooks)) return;

        members.emplace_back(id, name, email, phone, maxBooks);
        cout << "\nMember '" << name << "' (ID: " << id << ") added successfully!\n";
    }

    void issueBook() {
        cout << "\n=== ISSUE BOOK ===\n";
        string memberId, isbn;
        
        cout << "Enter Member ID: ";
        getline(cin >> ws, memberId);

        Member* member = findMember(memberId);
        if (!member || !member->getIsActive() || member->getIsDeleted()) {
            cout << "Member '" << memberId << "' not found or inactive!\n";
            return;
        }

        if (!member->canBorrow()) {
            cout << "Member '" << member->getName() << "' cannot borrow more books! " 
                 << "(Limit: " << member->getMaxBooks() << ", Current: " << member->getBorrowedBooks().size() << ")\n";
            return;
        }

        cout << "Enter Book ISBN: ";
        getline(cin, isbn);
        if (!isValidISBN(isbn)) {
            cout << "Invalid ISBN format!\n";
            return;
        }

        Book* book = findBook(isbn);
        if (!book || book->getIsDeleted()) {
            cout << "Book '" << isbn << "' not found!\n";
            return;
        }

        if (!book->isAvailable()) {
            cout << "Book '" << book->getTitle() << "' not available! (Copies left: " 
                 << book->getAvailableCopies() << ")\n";
            return;
        }

        int requestedCopies, maxPossible = min((int)(member->getMaxBooks() - member->getBorrowedBooks().size()), 
                                              book->getAvailableCopies());
        
        while (true) {
            cout << "\nBook: '" << book->getTitle() << "'" << endl;
            cout << "   Available copies: " << book->getAvailableCopies() << endl;
            cout << "   Member limit left: " << (member->getMaxBooks() - member->getBorrowedBooks().size()) << endl;
            cout << "   Max you can take: " << maxPossible << endl;
            cout << "How many copies? (1-" << maxPossible << "): ";
            
            string input;
            getline(cin >> ws, input);
            
            try {
                requestedCopies = stoi(input);
                if (requestedCopies >= 1 && requestedCopies <= maxPossible) {
                    break;
                } else {
                    cout << "Invalid! Only " << maxPossible << " copies available. Try again: ";
                }
            } catch (...) {
                cout << "Invalid number! Enter 1-" << maxPossible << ": ";
            }
        }

        for (int i = 0; i < requestedCopies; i++) {
            book->setAvailableCopies(book->getAvailableCopies() - 1);
            member->addBorrowedBook(isbn);
        }
        
        cout << "\n" << requestedCopies << " copies of '" << book->getTitle() 
             << "' issued to '" << member->getName() << "'!" << endl;
        cout << "Remaining: " << book->getAvailableCopies() << " | Member books: " 
             << member->getBorrowedBooks().size() << "/" << member->getMaxBooks() << endl;
    }

    void returnBook() {
        cout << "\n=== RETURN BOOK ===\n";
        string memberId, isbn;
        
        cout << "Enter Member ID: ";
        getline(cin >> ws, memberId);

        Member* member = findMember(memberId);
        if (!member || member->getIsDeleted()) {
            cout << "Member '" << memberId << "' not found!\n";
            return;
        }

        cout << "Enter Book ISBN: ";
        getline(cin, isbn);

        Book* book = findBook(isbn);
        if (!book || book->getIsDeleted()) {
            cout << "Book '" << isbn << "' not found!\n";
            return;
        }

        int copiesBorrowed = member->getBorrowedCopies(isbn);
        if (copiesBorrowed == 0) {
            cout << "Member '" << member->getName() << "' does not have this book!\n";
            return;
        }

        int returnCopies;
        while (true) {
            cout << "\n'" << book->getTitle() << "' - Member has " << copiesBorrowed << " copies" << endl;
            cout << "Tip: Enter '" << copiesBorrowed << "' to return ALL copies!" << endl;
            cout << "How many to return? (1-" << copiesBorrowed << "): ";
            
            string input;
            getline(cin >> ws, input);
            
            try {
                returnCopies = stoi(input);
                if (returnCopies >= 1 && returnCopies <= copiesBorrowed) {
                    break;
                } else {
                    cout << "Can return max " << copiesBorrowed << "! Try again: ";
                }
            } catch (...) {
                cout << "Invalid number! Enter 1-" << copiesBorrowed << ": ";
            }
        }

        bool success = member->returnBook(isbn, returnCopies);
        if (success) {
            book->setAvailableCopies(book->getAvailableCopies() + returnCopies);
        }
        
        cout << "\n" << returnCopies << " copies of '" << book->getTitle() 
             << "' returned by '" << member->getName() << "'!" << endl;
        cout << "Now available: " << book->getAvailableCopies() 
             << " | Member books: " << member->getBorrowedBooks().size() << "/" 
             << member->getMaxBooks() << endl;
    }

    void searchBooks() {
        string searchTerm;
        cout << "\n=== SEARCH BOOKS (Title/Author) ===\n";
        cout << "Enter title or author to search: ";
        getline(cin >> ws, searchTerm);

        bool found = false;
        cout << "\n" << left << setw(15) << "ISBN" << setw(25) << "Title" 
             << setw(20) << "Author" << setw(12) << "Genre" 
             << setw(8) << "Total" << setw(8) << "Available" << endl;
        cout << string(88, '-') << endl;

        for (const auto& book : books) {
            if (book.getIsDeleted()) continue;
            if (book.getTitle().find(searchTerm) != string::npos || 
                book.getAuthor().find(searchTerm) != string::npos) {
                cout << book.toString() << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No books found matching '" << searchTerm << "'!\n";
        }
    }

    void displayAllBooks() const {
        cout << "\n=== ALL BOOKS INVENTORY ===\n";
        cout << left << setw(15) << "ISBN" << setw(25) << "Title" 
             << setw(20) << "Author" << setw(12) << "Genre" 
             << setw(8) << "Total" << setw(8) << "Available" << endl;
        cout << string(88, '-') << endl;

        bool hasBooks = false;
        for (const auto& book : books) {
            if (!book.getIsDeleted()) {
                cout << book.toString() << endl;
                hasBooks = true;
            }
        }
        if (!hasBooks) cout << "No books available!\n";
    }

    void displayAllMembers() const {
        cout << "\n=== ALL MEMBERS ===\n";
        cout << left << setw(12) << "Member ID" << setw(20) << "Name" 
             << setw(25) << "Email" << setw(15) << "Phone" 
             << setw(12) << "Books/Max" << endl;
        cout << string(84, '-') << endl;

        bool hasMembers = false;
        for (const auto& member : members) {
            if (!member.getIsDeleted()) {
                cout << member.toString() << endl;
                hasMembers = true;
            }
        }
        if (!hasMembers) cout << "No members registered!\n";
    }

    void deleteBook() {
        string isbn;
        cout << "\nEnter ISBN to delete: ";
        getline(cin >> ws, isbn);

        for (auto& book : books) {
            if (book.getISBN() == isbn && !book.getIsDeleted()) {
                if (book.getAvailableCopies() == book.getTotalCopies()) {
                    book.setDeleted(true);
                    cout << "\nBook '" << book.getTitle() << "' marked as deleted!\n";
                    return;
                } else {
                    cout << "Cannot delete '" << book.getTitle() << "' - still issued out (" 
                         << (book.getTotalCopies() - book.getAvailableCopies()) << " copies)!\n";
                    return;
                }
            }
        }
        cout << "Book '" << isbn << "' not found!\n";
    }

    void deleteMember() {
        string id;
        cout << "\nEnter Member ID to delete: ";
        getline(cin >> ws, id);

        for (auto& member : members) {
            if (member.getMemberId() == id && !member.getIsDeleted()) {
                if (member.getBorrowedBooks().empty()) {
                    member.setDeleted(true);
                    cout << "\nMember '" << member.getName() << "' marked as deleted!\n";
                    return;
                } else {
                    cout << "Cannot delete '" << member.getName() << "' - has " 
                         << member.getBorrowedBooks().size() << " active books!\n";
                    return;
                }
            }
        }
        cout << "Member '" << id << "' not found!\n";
    }

    void saveData() const {
        ofstream bookFile("books.txt");
        ofstream memberFile("members.txt");

        for (const auto& book : books) {
            if (!book.getIsDeleted()) {
                bookFile << book.getISBN() << "|" << book.getTitle() << "|" 
                        << book.getAuthor() << "|" << book.getGenre() << "|"
                        << book.getTotalCopies() << "|" << book.getAvailableCopies() << endl;
            }
        }

        for (const auto& member : members) {
            if (!member.getIsDeleted() && member.getIsActive()) {
                stringstream ss;
                ss << member.getMemberId() << "|" << member.getName() << "|" 
                   << member.getEmail() << "|" << member.getPhone() << "|"
                   << member.getMaxBooks();
                for (const string& isbn : member.getBorrowedBooks()) {
                    ss << "|" << isbn;
                }
                memberFile << ss.str() << endl;
            }
        }

        bookFile.close();
        memberFile.close();
        cout << "\nData saved successfully!\n";
    }

    void loadData() {
        ifstream bookFile("books.txt");
        ifstream memberFile("members.txt");
        string line;

        books.clear();
        members.clear();

        if (bookFile.is_open()) {
            while (getline(bookFile, line)) {
                stringstream ss(line);
                string isbn, title, author, genre;
                int total, available;
                
                getline(ss, isbn, '|');
                getline(ss, title, '|');
                getline(ss, author, '|');
                getline(ss, genre, '|');
                ss >> total;
                ss.ignore();
                ss >> available;

                if (isValidISBN(isbn)) {
                    books.emplace_back(isbn, title, author, genre, total);
                    books.back().setAvailableCopies(available);
                }
            }
            bookFile.close();
        }

        if (memberFile.is_open()) {
            while (getline(memberFile, line)) {
                stringstream ss(line);
                string id, name, email, phone;
                int maxBooks;
                
                getline(ss, id, '|');
                getline(ss, name, '|');
                getline(ss, email, '|');
                getline(ss, phone, '|');
                ss >> maxBooks;

                if (email.find('@') != string::npos && phone.length() == 10) {
                    Member member(id, name, email, phone, maxBooks);
                    string isbn;
                    while (getline(ss, isbn, '|')) {
                        if (!isbn.empty()) {
                            member.addBorrowedBook(isbn);
                        }
                    }
                    members.push_back(member);
                }
            }
            memberFile.close();
        }
        cout << "\nData loaded successfully!\n";
    }

private:
    Book* findBook(const string& isbn) {
        for (auto& book : books) {
            if (book.getISBN() == isbn) return &book;
        }
        return nullptr;
    }

    Member* findMember(const string& id) {
        for (auto& member : members) {
            if (member.getMemberId() == id) return &member;
        }
        return nullptr;
    }
};

void displayMenu() {
    cout << "\n=====================================";
    cout << "\n    LIBRARY MANAGEMENT SYSTEM";
    cout << "\n=====================================";
    cout << "\n1.   Add Book";
    cout << "\n2.   Add Member";
    cout << "\n3.   Issue Book";
    cout << "\n4.   Return Book";
    cout << "\n5.   Search Books";
    cout << "\n6.   Display All Books";
    cout << "\n7.   Display All Members";
    cout << "\n8.   Delete Book";
    cout << "\n9.   Delete Member";
    cout << "\n10.  Save Data";
    cout << "\n11.  Load Data";
    cout << "\n0.   Exit";
    cout << "\n=====================================";
    cout << "\nEnter your choice: ";
}

int main() {
    Library library("Central Library");
    int choice;

    library.loadData();

    while (true) {
        system("clear || cls");
        displayMenu();
        
        if (!(cin >> choice)) {
            cout << "\nInvalid input! Please enter a number (0-11).\n";
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Press Enter to continue...";
            cin.get();
            continue;
        }
        cin.ignore();

        switch (choice) {
            case 1:  library.addBook(); break;
            case 2:  library.addMember(); break;
            case 3:  library.issueBook(); break;
            case 4:  library.returnBook(); break;
            case 5:  library.searchBooks(); break;
            case 6:  library.displayAllBooks(); break;
            case 7:  library.displayAllMembers(); break;
            case 8:  library.deleteBook(); break;
            case 9:  library.deleteMember(); break;
            case 10: library.saveData(); break;
            case 11: library.loadData(); break;
            case 0:
                library.saveData();
                cout << "\nThank you for using Library Management System!\n";
                return 0;
            default:
                cout << "\nInvalid choice! Please enter 0-11.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.get();
    }

    return 0;
}