#include "Accountant.h"
#include <iostream>

Accountant::Accountant(const std::string& name, int age, int id, const std::string& department)
    : Human(name, age, id), department(department) {}

void Accountant::work() {

    std::cout << "Бухгалтер " << getName() << " из отдела " << getDepartment() << " считает зарплату";
    // вывести сообщение: "Бухгалтер [имя] из отдела [department] считает зарплату"
}

std::string Accountant::getDepartment() const {
    return department;
}
