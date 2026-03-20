#include "Worker.h"
#include <iostream>
#include "Machine.h"

Worker::Worker(const std::string& name, int age, int id, int experience)
    : Human(name, age, id), experience(experience), currentMachine(nullptr) {}

void Worker::work() {

    if (currentMachine != nullptr){
        currentMachine->process();
    }
    else {
        std::cout << "Рабочий не закреплен за станком! Не может начать работу" << std::endl;
    }
}

void Worker::assignMachine(Machine* machine) {
    currentMachine = machine;
}

Machine* Worker::getCurrentMachine() const {
    return currentMachine;
}

int Worker::getExperience() const {
    return experience;
}
