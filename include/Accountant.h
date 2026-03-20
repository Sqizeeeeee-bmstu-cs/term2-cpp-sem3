#ifndef ACCOUNTANT_H
#define ACCOUNTANT_H

#include "Human.h"

class Accountant : public Human {
private:
    std::string department;

public:
    Accountant(const std::string& name, int age, int id, const std::string& department);
    
    void work() override;
    std::string getDepartment() const;
};

#endif
