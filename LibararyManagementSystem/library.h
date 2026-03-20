#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include "Book.h"
#include "Member.h"

class Library
{
private:
    std::vector<Book*> books;
    std::vector<Member*>members;
public:
    void addBook(Book* book);
    void registerMember(Member* member);

    Book* findBook(int bookID);
    Member* findMember(int memberID);

    bool borrowBook(int memberID, int bookID);
    bool returnBook(int memberID, int bookID);
    void displayAllBooks() const;
    void generateReport() const;
};

#endif

