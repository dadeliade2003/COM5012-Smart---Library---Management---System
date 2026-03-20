#include "person.h"
#include <iostream>

Person::Person(int id, std::string name)
    : id(id), name(name) {}

int Person::getId() const { return id; }
std::string Person::getName() const { return name; }

void Person::displayRole() const {
    std::cout << "Person\n";
}
