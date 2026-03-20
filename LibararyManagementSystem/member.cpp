#include "member.h"
#include <iostream>

Member::Member(int id, const std::string& name)
    : User(id, name), borrowedBooks(0)
{
}

bool Member::borrowBook(Book* book)
{
    if (book == nullptr) return false;
    if (borrowedBooks >= MAX_BORROW) return false;
    if (book->getStatus() == BookStatus::Available) {
        book->setStatus(BookStatus::Borrowed);
        book->setDueInDays(14);
        ++borrowedBooks;
        return true;
    }
    return false;
}

bool Member::returnBook(Book* book)
{
    if (book == nullptr) return false;
    if (book->getStatus() == BookStatus::Borrowed) {
        book->setStatus(BookStatus::Available);
        --borrowedBooks;
        return true;
    }
    return false;
}

void Member::reserveBook(Book* book)
{
    if (book == nullptr) return;
    // Simple reservation: store pointer locally. More advanced logic can be added.
    reservedBooks.push_back(book);
}

int Member::getBorrowedBooks() const
{
    return borrowedBooks;
}

int Member::getMemberID() const {
    return getId();
}

void Member::displayRole() const
{
    std::cout << "Member user\n";
}
