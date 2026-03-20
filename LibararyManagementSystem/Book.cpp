#include "Book.h"
#include <iostream>

Book::Book(int id, const std::string& t, const std::string& a)
    : bookID(id), title(t), author(a), status(BookStatus::Available),
      daysUntilDue(0), reservedById(0)
{
}

int Book::getBookID() const { return bookID; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
BookStatus Book::getStatus() const { return status; }
void Book::setStatus(BookStatus newStatus) { status = newStatus; }

void Book::setDueInDays(int days) { daysUntilDue = days; }
bool Book::isOverdue() const { return daysUntilDue < 0; }

void Book::setReservedBy(int memberId) { reservedById = memberId; }
int Book::getReservedBy() const { return reservedById; }

void Book::display() const {
    std::cout << "Book ID: " << bookID
        << ", Title: " << title
        << ", Author: " << author
        << ", Status: ";
    switch (status) {
        case BookStatus::Available: std::cout << "Available"; break;
        case BookStatus::Borrowed: std::cout << "Borrowed"; break;
        case BookStatus::Reserved: std::cout << "Reserved"; break;
    }
    std::cout << std::endl;
}
