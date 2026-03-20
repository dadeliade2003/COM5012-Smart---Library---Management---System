#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>
#include "user.h"
#include "Book.h"

class Member : public User {
public:
    Member(int id, const std::string& name);
    bool borrowBook(Book* book);
    bool returnBook(Book* book);
    void reserveBook(Book* book);
    int getBorrowedBooks() const;
    int getMemberID() const;
    void displayRole() const override;

private:
    int borrowedBooks;
    std::vector<Book*> reservedBooks;
    static const int MAX_BORROW = 5;
};

#endif // MEMBER_H

