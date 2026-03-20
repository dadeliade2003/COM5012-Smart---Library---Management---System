#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
#include <string>
#include <vector>
#include "member.h"

class Admin : public User {
public:
    Admin(int id, std::string name);

    // Create a new member and add to a list
    void createMember(int id, const std::string& name, std::vector<Member>& members);

    // Remove member by ID (very simple version)
    void removeMember(int id, std::vector<Member>& members);

    void displayRole() const override;
};

#endif // ADMIN_H

