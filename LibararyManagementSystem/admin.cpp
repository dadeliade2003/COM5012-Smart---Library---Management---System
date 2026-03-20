#include "admin.h"
#include <iostream>

Admin::Admin(int id, std::string name)
    : User(id, name) {
}

void Admin::createMember(int id, const std::string& name, std::vector<Member>& members)
{
    members.emplace_back(id, name);
    std::cout << "Admin created member with ID " << id
        << " and name " << name << "\n";
}

void Admin::removeMember(int id, std::vector<Member>& members)
{
    for (auto it = members.begin(); it != members.end(); ++it) {
        if (it->getId() == id) {
            std::cout << "Admin removed member with ID " << id << "\n";
            members.erase(it);
            return;
        }
    }
    std::cout << "Member with ID " << id << " not found\n";
}

void Admin::displayRole() const
{
    std::cout << "Admin user\n";
}
