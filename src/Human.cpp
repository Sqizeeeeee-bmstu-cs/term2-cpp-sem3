#include "Human.h"

Human::Human(const std::string& name, int age, int id)
    : name(name), age(age), id(id) {}

std::string Human::getName() const {
    return name;
}

int Human::getAge() const {
    return age;
}

int Human::getId() const {
    return id;
}
