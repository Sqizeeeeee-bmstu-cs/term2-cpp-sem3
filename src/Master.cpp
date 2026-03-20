#include "Master.h"
#include "Worker.h"
#include <iostream>
#include <algorithm>

Master::Master(const std::string& name, int age, int id)
    : Human(name, age, id) {}

void Master::work() {
    std::cout << "Мастер " << getName() << " управляет бригадой из " 
              << team.size() << " рабочих" << std::endl;
}

void Master::addWorker(Worker* worker) {
    team.push_back(worker);
}

void Master::removeWorker(int workerId) {
    auto it = std::remove_if(team.begin(), team.end(),
        [workerId](Worker* worker) {
            return worker->getId() == workerId;
        });
    team.erase(it, team.end());
}

const std::vector<Worker*>& Master::getTeam() const {
    return team;
}
