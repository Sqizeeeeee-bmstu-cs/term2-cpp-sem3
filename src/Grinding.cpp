#include "Grinding.h"
#include <iostream>

Grinding::Grinding(const std::string& model, int power, double precision)
    : Machine(model, power), precision(precision) {}

void Grinding::process() {
    if (!getIsWorking()) {
        start();
    }
    std::cout << "Шлифовальный станок " << getModel() << " шлифует поверхность" << std::endl;
}

double Grinding::getPrecision() const {
    return precision;
}
