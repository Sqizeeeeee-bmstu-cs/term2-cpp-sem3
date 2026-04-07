#include "Lathe.h"
#include <iostream>

Lathe::Lathe(const std::string& model, int power, double maxDiameter)
    : Machine(model, power), maxDiameter(maxDiameter) {}

void Lathe::process() {
    if (!getIsWorking()){
        start();
    }
    
    std::cout << "Станок " << getModel() << " работает" << std::endl;
}

double Lathe::getMaxDiameter() const {
    return maxDiameter;
}

std::string Lathe::getType() const {
    return "Токарный станок";
}
