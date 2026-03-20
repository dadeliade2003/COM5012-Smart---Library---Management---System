
#ifndef BOOK_H
#define BOOK_H

#include <string>

enum class BookStatus {
    Available,
    Borrowed,
    Reserved
};

class Book {
public:
    Book(int id, const std::string& t, const std::string& a);

    int getBookID() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    BookStatus getStatus() const;
    void setStatus(BookStatus newStatus);
    void display() const;

    // Simple due-date helpers used by tests
    void setDueInDays(int days);
    bool isOverdue() const;

    // Optional reservation holder (member id), 0 == none
    void setReservedBy(int memberId);
    int getReservedBy() const;

private:
    int bookID;
    std::string title;
    std::string author;
    BookStatus status;
    int daysUntilDue;
    int reservedById;
};

#endif // BOOK_H
