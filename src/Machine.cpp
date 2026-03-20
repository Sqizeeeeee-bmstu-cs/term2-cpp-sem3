#include "Machine.h"

Machine::Machine(const std::string& model, int power)
    : model(model), power(power), isWorking(false) {}

std::string Machine::getModel() const {
    return model;
}

int Machine::getPower() const {
    return power;
}

bool Machine::getIsWorking() const {
    return isWorking;
}

void Machine::start() {
    isWorking = true;
}

void Machine::stop() {
    isWorking = false;
}
