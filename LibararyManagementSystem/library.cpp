#include "library.h"
#include "Book.h"
#include "member.h"
#include <iostream>

void Library::addBook(Book* book) {
    books.push_back(book);
}

void Library::registerMember(Member* member) {
    members.push_back(member);
}

Book* Library::findBook(int bookID) {
    for (auto b : books) {
        if (b->getBookID() == bookID) return b;
    }
    return nullptr;
}

Member* Library::findMember(int memberID) {
    for (auto m : members) {
        if (m->getMemberID() == memberID) return m;
    }
    return nullptr;
}

bool Library::borrowBook(int memberID, int bookID) {
    Book* book = findBook(bookID);
    Member* member = findMember(memberID);
    if (book == nullptr || member == nullptr) return false;
    if (book->getStatus() == BookStatus::Borrowed) return false;
    return member->borrowBook(book);
}

bool Library::returnBook(int memberID, int bookID) {
    Book* book = findBook(bookID);
    Member* member = findMember(memberID);
    if (book == nullptr || member == nullptr) return false;
    return member->returnBook(book);
}

void Library::displayAllBooks() const {
    std::cout << "\n=== LIBRARY BOOKS ===\n";
    for (auto b : books) {
        b->display();
    }
}

void Library::generateReport() const {
    std::cout << "\n=== REPORT ===\n";
    std::cout << "Total books: " << books.size() << std::endl;
}

