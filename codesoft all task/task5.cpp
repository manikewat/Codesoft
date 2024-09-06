#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <iomanip>

class Book {
public:
    Book(int id, const std::string& title, const std::string& author, const std::string& isbn, int totalCopies)
        : id(id), title(title), author(author), isbn(isbn), totalCopies(totalCopies), availableCopies(totalCopies) {}

    int getId() const { return id; }
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getISBN() const { return isbn; }
    int getAvailableCopies() const { return availableCopies; }
    
    void incrementAvailableCopies() { availableCopies++; }
    void decrementAvailableCopies() { availableCopies--; }

private:
    int id;
    std::string title;
    std::string author;
    std::string isbn;
    int totalCopies;
    int availableCopies;
};

class Transaction {
public:
    Transaction(int bookId, int borrowerId, const std::tm& checkoutDate, const std::tm& dueDate)
        : bookId(bookId), borrowerId(borrowerId), checkoutDate(checkoutDate), dueDate(dueDate) {}

    int getBookId() const { return bookId; }
    int getBorrowerId() const { return borrowerId; }
    std::tm getDueDate() const { return dueDate; }

private:
    int bookId;
    int borrowerId;
    std::tm checkoutDate;
    std::tm dueDate;
};

class BookDatabase {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    Book* searchByTitle(const std::string& title) {
        for (auto& book : books) {
            if (book.getTitle() == title) {
                return &book;
            }
        }
        return nullptr;
    }

    Book* searchByISBN(const std::string& isbn) {
        for (auto& book : books) {
            if (book.getISBN() == isbn) {
                return &book;
            }
        }
        return nullptr;
    }

    Book* getBookById(int id) {
        for (auto& book : books) {
            if (book.getId() == id) {
                return &book;
            }
        }
        return nullptr;
    }

private:
    std::vector<Book> books;
};

class TransactionManager {
public:
    void checkoutBook(int bookId, int borrowerId, const std::tm& checkoutDate, const std::tm& dueDate) {
        transactions.emplace(nextTransactionId++, Transaction(bookId, borrowerId, checkoutDate, dueDate));
    }

    Transaction* getTransactionByBookId(int bookId) {
        for (auto& txn : transactions) {
            if (txn.second.getBookId() == bookId) {
                return &txn.second;
            }
        }
        return nullptr;
    }

    void removeTransaction(int transactionId) {
        transactions.erase(transactionId);
    }

private:
    std::map<int, Transaction> transactions;
    int nextTransactionId = 1;
};

int calculateFine(const std::tm& dueDate, const std::tm& returnDate) {
    std::time_t due = std::mktime(const_cast<std::tm*>(&dueDate));
    std::time_t returned = std::mktime(const_cast<std::tm*>(&returnDate));
    int daysOverdue = (returned - due) / (60 * 60 * 24);
    
    if (daysOverdue > 0) {
        return daysOverdue * 1;  // Example fine of $1 per day overdue
    }
    return 0;
}

void searchBooks(BookDatabase& db) {
    std::string query;
    std::cout << "Enter book title or ISBN to search: ";
    std::cin.ignore();
    std::getline(std::cin, query);

    Book* book = db.searchByTitle(query);
    if (book == nullptr) {
        book = db.searchByISBN(query);
    }

    if (book != nullptr) {
        std::cout << "Book Found: " << book->getTitle() << " by " << book->getAuthor() << std::endl;
    } else {
        std::cout << "Book not found." << std::endl;
    }
}

void checkoutBook(BookDatabase& db, TransactionManager& txnManager) {
    int bookId;
    int borrowerId;
    std::tm checkoutDate = {};
    std::tm dueDate = {};

    std::cout << "Enter book ID to checkout: ";
    std::cin >> bookId;
    std::cout << "Enter borrower ID: ";
    std::cin >> borrowerId;

    Book* book = db.getBookById(bookId);
    if (book && book->getAvailableCopies() > 0) {
        book->decrementAvailableCopies();
        
        // Set checkoutDate and dueDate (simplified)
        std::time_t now = std::time(nullptr);
        checkoutDate = *std::localtime(&now);
        dueDate = checkoutDate;
        dueDate.tm_mday += 14;  // Example: Due date 2 weeks from checkout
        std::mktime(&dueDate);

        txnManager.checkoutBook(bookId, borrowerId, checkoutDate, dueDate);
        std::cout << "Book checked out successfully." << std::endl;
    } else {
        std::cout << "Book is not available." << std::endl;
    }
}

void returnBook(BookDatabase& db, TransactionManager& txnManager) {
    int bookId;
    std::tm returnDate = {};

    std::cout << "Enter book ID to return: ";
    std::cin >> bookId;

    Book* book = db.getBookById(bookId);
    if (book) {
        book->incrementAvailableCopies();
        Transaction* txn = txnManager.getTransactionByBookId(bookId);
        
        if (txn) {
            std::time_t now = std::time(nullptr);
            returnDate = *std::localtime(&now);
            
            int fine = calculateFine(txn->getDueDate(), returnDate);
            txnManager.removeTransaction(txn->getBookId());
            
            std::cout << "Book returned successfully." << std::endl;
            if (fine > 0) {
                std::cout << "You have a fine of $" << fine << std::endl;
            }
        } else {
            std::cout << "No transaction found for this book." << std::endl;
        }
    } else {
        std::cout << "Invalid book ID." << std::endl;
    }
}

int main() {
    BookDatabase bookDb;
    TransactionManager txnManager;

    // Add some books to the database
    bookDb.addBook(Book(1, "1984", "George Orwell", "1234567890123", 5));
    bookDb.addBook(Book(2, "To Kill a Mockingbird", "Harper Lee", "1234567890124", 3));

    while (true) {
        std::cout << "Library Management System" << std::endl;
        std::cout << "1. Search Books" << std::endl;
        std::cout << "2. Checkout Book" << std::endl;
        std::cout << "3. Return Book" << std::endl;
        std::cout << "4. Exit" << std::endl;

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                searchBooks(bookDb);
                break;
            case 2:
                checkoutBook(bookDb, txnManager);
                break;
            case 3:
                returnBook(bookDb, txnManager);
                break;
            case 4:
                return 0;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
                break;
        }
    }

    return 0;
}
