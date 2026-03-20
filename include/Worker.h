#ifndef WORKER_H
#define WORKER_H

#include "Human.h"

class Machine;

class Worker : public Human {
private:
    Machine* currentMachine;
    int experience;

public:
    Worker(const std::string& name, int age, int id, int experience);
    
    void work() override;
    
    void assignMachine(Machine* machine);
    Machine* getCurrentMachine() const;
    int getExperience() const;
};

#endif
