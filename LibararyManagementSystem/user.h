#ifndef USER_H
#define USER_H

#include "person.h"
#include <string>

class User : public Person
{
public:
    User(int id, std::string n);
    int getUserID() const;
    virtual void displayRole() const;  // polymorphic function
    virtual ~User() {}  // virtual destructor
};

#endif
