#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include "Book.h"
#include "member.h"
#include "admin.h"

using namespace std;
void showOverdueBooks(const vector<Book*>& books) {
    cout << "\n=== Overdue Books ===\n";
    bool foundAny = false;
    for (const auto& b : books) {
        if (b->isOverdue()) {
            foundAny = true;
            cout << "  " << b->getTitle() << " (ID: " << b->getBookID()
                 << ", Author: " << b->getAuthor() << ")\n";
        }
    }
    if (!foundAny) cout << "  There are no overdue books at the moment.\n";
}

void printLibrarySummary(const std::vector<Book*>& books,
    const std::vector<Member>& members)
{
    std::cout << "\n=== Library Summary ===\n";

    std::cout << "Total books in system: " << books.size() << "\n";
    std::cout << "Total members in system: " << members.size() << "\n";

    int borrowedCount = 0;
    int availableCount = 0;
    int reservedCount = 0;

    for (const auto& book : books)
    {
        if (book->getStatus() == BookStatus::Borrowed)
            borrowedCount++;
        else if (book->getStatus() == BookStatus::Available)
            availableCount++;
        else if (book->getStatus() == BookStatus::Reserved)
            reservedCount++;
    }

    std::cout << "Available books: " << availableCount << "\n";
    std::cout << "Borrowed books: " << borrowedCount << "\n";
    std::cout << "Reserved books: " << reservedCount << "\n";
}

void searchBooksByTitle(const vector<Book*>& books, const string& queryTitle) {
    cout << "\nSearching for books with title containing: '" << queryTitle << "'\n";
    string lowerQuery = queryTitle;
    transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);
    bool foundAny = false;
    for (const auto& b : books) {
        string title = b->getTitle();
        string lowerTitle = title;
        transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);
        if (lowerTitle.find(lowerQuery) != string::npos) {
            foundAny = true;
            cout << "  Found book: " << title << " (ID: " << b->getBookID()
                 << ", Author: " << b->getAuthor() << ")\n";
        }
    }
    if (!foundAny) cout << "  No books found matching that title.\n";
}
// find member helper
Member* findMemberById(std::vector<Member>& members, int memberId)
{
    for (auto& m : members)
    {
        if (m.getId() == memberId)
        {
            return &m;
        }
    }
    return nullptr;
}

void simulateLoginById(std::vector<Member>& members,
    const std::vector<Book*>& books)
{
    std::cout << "\n=== Simulated Member Login ===\n";
    std::cout << "Enter member ID to log in: ";

    int id;
    std::cin >> id;

    Member* loggedIn = findMemberById(members, id);

    if (loggedIn == nullptr)
    {
        std::cout << "Login failed: no member with ID " << id << ".\n";
        return;
    }

    std::cout << "Login successful. Welcome, "
        << loggedIn->getName() << " (ID: " << loggedIn->getId() << ").\n";

    // For coursework, we just show some information after login.
    std::cout << "Here are your currently borrowed books:\n";

    // Reuse your existing function if you want:
    // listBorrowedBooksForMember(books, *loggedIn);
}


int main() {
    // Admin demo
    vector<Member> allMembers;
    Member alice(1, "Alice");
    allMembers.push_back(alice);

    Admin admin1(100, "Super Admin");
    cout << "\n===== Admin Demo =====\n";
    admin1.displayRole(); // shows polymorphism

    cout << "Creating a new member via Admin...\n";
    admin1.createMember(2, "Bob", allMembers);

    cout << "Current members:\n";
    for (const auto& m : allMembers) {
        cout << " - ID: " << m.getId() << ", Name: " << m.getName() << "\n";
    }

    cout << "Removing member with ID 1 via Admin...\n";
    admin1.removeMember(1, allMembers);

    cout << "Members after removal:\n";
    for (const auto& m : allMembers) {
        cout << " - ID: " << m.getId() << ", Name: " << m.getName() << "\n";
    }

    // Automated tests
    cout << "\n===== Automated Tests =====\n";

    vector<Book*> books = {
        new Book(1, "1984", "George Orwell"),
        new Book(2, "The Hobbit", "J.R.R. Tolkien"),
        new Book(3, "Pride and Prejudice", "Jane Austen"),
        new Book(4, "Dune", "Frank Herbert"),
        new Book(5, "Hamlet", "Shakespeare"),
        new Book(6, "The Alchemist", "Paulo Coelho")
    };

    // Demonstrate search and overdue helpers
    showOverdueBooks(books);
    searchBooksByTitle(books, "Harry");
    searchBooksByTitle(books, "Data Structures");

    Member testMember(10, "TestUser");

    cout << "\nTest 1: Borrow 5 books (should succeed)\n";
    for (int i = 0; i < 5; ++i) {
        bool ok = testMember.borrowBook(books[i]);
        cout << "Borrowing book " << books[i]->getBookID() << ": " << (ok ? "OK" : "FAIL") << "\n";
    }

    cout << "\nTest 2: Borrow 6th book (should fail: limit reached)\n";
    bool ok6 = testMember.borrowBook(books[5]);
    cout << "Borrowing book " << books[5]->getBookID() << ": " << (ok6 ? "OK" : "FAIL") << "\n";

    cout << "\nMember currently has " << testMember.getBorrowedBooks() << " book(s).\n";

    // Test 3: Overdue check
    cout << "\nTest 3: Overdue check\n";
    books[0]->setDueInDays(-1); // negative => overdue
    cout << "Book 1 is " << (books[0]->isOverdue() ? "overdue" : "not overdue") << ".\n";

    // Test 4: Reservation of borrowed book
    cout << "\nTest 4: Reservation of borrowed book\n";
    Member member2(2, "Bob");
    cout << "TestUser borrows Book 2\n";
    testMember.borrowBook(books[1]);
    cout << "Bob tries to reserve Book 2\n";
    member2.reserveBook(books[1]);
    cout << "Bob tries to borrow Book 2\n";
    bool bobOk = member2.borrowBook(books[1]);
    cout << "Bob borrowing Book 2: " << (bobOk ? "OK" : "FAIL") << "\n";


    cout << "\nTest 5: Return book that was never borrowed\n";
    Book neverBorrowed(99, "Random Book", "Unknown");
    testMember.returnBook(&neverBorrowed);   // should print a failure message
    cout << "\nTest 6: Reserve available book (should fail)\n";
    Book availableBook(100, "Available Only", "Someone");
    testMember.reserveBook(&availableBook);
    cout << "\nTest 7: Polymorphism via Person*\n";
    Person* p1 = &testMember;
    p1->displayRole();   // should call Member::displayRole

    // Print a summary of the library state
    printLibrarySummary(books, allMembers);


    // Cleanup
    for (auto b : books) delete b;
    return 0;
}
