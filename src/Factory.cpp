#include "Factory.h"
#include "Workshop.h"
#include "Human.h"
#include <iostream>
#include <algorithm>

Factory::Factory(const std::string& name)
    : name(name) {}


std::string Factory::getName() const {
    return name;
}

void Factory::addWorkshop(const std::string& workshopName) {
    workshops.push_back(std::make_unique<Workshop>(workshopName));
}

Workshop* Factory::getWorkshop(const std::string& name) const {
    for (const auto& workshop : workshops) {
        if (workshop->getName() == name){
            return workshop.get();
        }
    }
    return nullptr;
}

const std::vector<std::unique_ptr<Workshop>>& Factory::getWorkshops() const {
    return workshops;
}

void Factory::hireWorker(Human* worker) {
    workers.push_back(worker);
}

void Factory::fireWorker(int id) {
    auto it = std::remove_if(workers.begin(), workers.end(),
        [id](Human* human) {
            return human->getId() == id;
        });
    workers.erase(it, workers.end());

}

const std::vector<Human*>& Factory::getWorkers() const {
    return workers;
}

void Factory::showInfo() const {
    
    std::cout << name << std::endl;

    for (const auto& worker : workers){
        std::cout << worker->getName() << " " << worker->getAge() << std::endl;
    }

    for (const auto& workshop : workshops){
        std::cout << workshop->getName() << " " << std::endl;
        workshop->showMachines();
    }
}
