#ifndef HUMAN_H
#define HUMAN_H

#include <string>

class Machine;

class Human {
private:
    std::string name;
    int age;
    int id;

public:
    Human(const std::string& name, int age, int id);
    virtual ~Human() = default;

    std::string getName() const;
    int getAge() const;
    int getId() const;

    virtual void work() = 0;
};

#endif
