#include "Milling.h"
#include <iostream>

Milling::Milling(const std::string& model, int power, int spindleSpeed)
    : Machine(model, power), spindleSpeed(spindleSpeed) {}

void Milling::process() {
    if (!getIsWorking()) {
        start();
    }
    std::cout << "Фрезерный станок " << getModel() << " фрезерует заготовку" << std::endl;
}

int Milling::getSpindleSpeed() const {
    return spindleSpeed;
}

std::string Milling::getType() const {
    return "Фрезерный станок";
}
