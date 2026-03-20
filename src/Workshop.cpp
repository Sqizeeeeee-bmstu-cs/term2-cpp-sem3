#include "Workshop.h"
#include "Machine.h"
#include <iostream>

Workshop::~Workshop() = default;

Workshop::Workshop(const std::string& name)
    : name(name) {}

std::string Workshop::getName() const {
    return name;
}

void Workshop::addMachine(Machine* machine) {
    machines.push_back(std::unique_ptr<Machine>(machine));
}

const std::vector<std::unique_ptr<Machine>>& Workshop::getMachines() const {
    return machines;
}

void Workshop::showMachines() const {
    for (const auto& curr : machines) {
        std::cout << "Станок " << curr->getModel() << std::endl;
    }
}
