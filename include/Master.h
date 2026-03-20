#ifndef MASTER_H
#define MASTER_H

#include "Human.h"
#include <vector>

class Worker;

class Master : public Human {
private:
    std::vector<Worker*> team;

public:
    Master(const std::string& name, int age, int id);
    
    void work() override;
    void addWorker(Worker* worker);
    void removeWorker(int workerId);
    const std::vector<Worker*>& getTeam() const;
};

#endif
