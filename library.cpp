
#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <ctime>
#include <sstream>
#include <string>
#include <algorithm>  // For std::sort

using namespace std;

struct Book {
    string title;
    string author;
    string genre;
    int publicationYear;
    bool isIssued;
    string issuedTo;
    time_t issueDate;

    // Constructor
    Book(string t, string a, string g, int pYear)
        : title(t), author(a), genre(g), publicationYear(pYear), isIssued(false), issuedTo("") {}

    // Function to get the formatted issue date
    string getIssueDate() const {
        if (isIssued) {
            char buffer[80];
            struct tm* timeinfo = localtime(&issueDate);
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
            return string(buffer);
        } else {
            return "Not Issued";
        }
    }
};

class Library {
public:
    vector<Book> books;

    void addBook(const string& title, const string& author, const string& genre, int publicationYear) {
        books.push_back(Book(title, author, genre, publicationYear));
    }

    void issueBook(const string& title, const string& memberName) {
        for (auto& book : books) {
            if (book.title == title && !book.isIssued) {
                book.isIssued = true;
                book.issuedTo = memberName;
                time(&book.issueDate);
                cout << "Book '" << title << "' has been issued to " << memberName << endl;
                return;
            }
        }
        cout << "Book is either not available or already issued.\n";
    }

    void returnBook(const string& title) {
        for (auto& book : books) {
            if (book.title == title && book.isIssued) {
                book.isIssued = false;
                book.issuedTo = "";
                cout << "Book '" << title << "' has been returned.\n";
                return;
            }
        }
        cout << "This book wasn't issued or doesn't exist in the library.\n";
    }

    void searchBookByTitle(const string& title) {
        for (const auto& book : books) {
            if (book.title.find(title) != string::npos) {
                displayBook(book);
            }
        }
    }

    void searchBookByAuthor(const string& author) {
        for (const auto& book : books) {
            if (book.author.find(author) != string::npos) {
                displayBook(book);
            }
        }
    }

    void displayAllBooks() {
        for (const auto& book : books) {
            displayBook(book);
        }
    }

private:
    void displayBook(const Book& book) {
        cout << "Title: " << book.title
             << ", Author: " << book.author
             << ", Genre: " << book.genre
             << ", Publication Year: " << book.publicationYear
             << ", Status: " << (book.isIssued ? "Issued to " + book.issuedTo : "Available")
             << ", Issue Date: " << book.getIssueDate() << endl;
    }
};

int main() {
    Library library;
    int choice;
    
    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n2. Issue Book\n3. Return Book\n4. Search Book by Title\n5. Search Book by Author\n6. Display All Books\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character after the choice

        if (choice == 1) {
            string title, author, genre;
            int publicationYear;

            cout << "Enter book title: ";
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);
            cout << "Enter genre: ";
            getline(cin, genre);
            cout << "Enter publication year: ";
            cin >> publicationYear;

            library.addBook(title, author, genre, publicationYear);
            cout << "Book added successfully.\n";
        } else if (choice == 2) {
            string title, memberName;

            cout << "Enter book title: ";
            getline(cin, title);
            cout << "Enter member's name: ";
            getline(cin, memberName);

            library.issueBook(title, memberName);
        } else if (choice == 3) {
            string title;

            cout << "Enter book title: ";
            getline(cin, title);

            library.returnBook(title);
        } else if (choice == 4) {
            string title;

            cout << "Enter book title: ";
            getline(cin, title);

            library.searchBookByTitle(title);
        } else if (choice == 5) {
            string author;

            cout << "Enter author's name: ";
            getline(cin, author);

            library.searchBookByAuthor(author);
        } else if (choice == 6) {
            library.displayAllBooks();
        } else if (choice == 7) {
            cout << "Exiting program...\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
