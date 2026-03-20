#include "user.h"
#include <iostream>

User::User(int id, std::string n)
    : Person(id, n)
{
}

int User::getUserID() const
{
    return getId();
}

void User::displayRole() const
{
    // Default role display for a generic user
    std::cout << "User\n";
}
