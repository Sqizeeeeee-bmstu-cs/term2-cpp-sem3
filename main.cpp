#include "Container.h"
#include "Lathe.h"
#include "Milling.h"
#include "Grinding.h"
#include "Worker.h"
#include "Accountant.h"
#include <iostream>
#include <algorithm>
#include <string>


void printMachineInfo(const Machine& m) {
    std::cout << "  Тип: " << m.getType() 
              << ", Модель: " << m.getModel() 
              << ", Мощность: " << m.getPower() << " кВт" << std::endl;
}

void printHumanInfo(const Human& h) {
    std::cout << "  Имя: " << h.getName() 
              << ", Возраст: " << h.getAge() 
              << ", ID: " << h.getId() << std::endl;
}

bool compareMachinePower(const Machine* a, const Machine* b) {
    return a->getPower() < b->getPower();
}

bool compareWorkerAge(const Human* a, const Human* b) {
    return a->getAge() < b->getAge();
}

struct FindMachineByModel {
    std::string target;
    FindMachineByModel(const std::string& t) : target(t) {}
    bool operator()(const Machine* m) const {
        return m->getModel() == target;
    }
};

struct FindHumanByName {
    std::string target;
    FindHumanByName(const std::string& t) : target(t) {}
    bool operator()(const Human* h) const {
        return h->getName() == target;
    }
};

int main() {
    std::cout << "=== Демонстрация шаблонного контейнера MyContainer<T> ===\n\n";

    std::cout << "--- 1. Контейнер MyContainer<Machine*> (станки) ---\n";

    MyContainer<Machine*> machineContainer;

    machineContainer.push_back(new Lathe("16K20", 11, 400));
    machineContainer.push_back(new Milling("6R12", 7, 1600));
    machineContainer.push_back(new Lathe("1K62", 10, 300));
    machineContainer.push_back(new Grinding("3M174", 5, 0.002));
    machineContainer.push_back(new Milling("VM-1", 4, 12000));

    std::cout << "Добавлено станков: " << machineContainer.getSize() << "\n\n";

    std::cout << "Перебор станков (через итераторы):\n";
    for (auto it = machineContainer.begin(); it != machineContainer.end(); ++it) {
        printMachineInfo(*(*it));
    }

    std::cout << "\nПеребор станков (диапазонный for):\n";
    for (const auto& m : machineContainer) {
        printMachineInfo(*m);
    }

    std::cout << "\nПоиск станка с моделью '1K62':\n";
    auto it = std::find_if(machineContainer.begin(), machineContainer.end(), 
                           FindMachineByModel("1K62"));
    if (it != machineContainer.end()) {
        std::cout << "  Найден: ";
        printMachineInfo(*(*it));
    } else {
        std::cout << "  Станок не найден\n";
    }

    std::cout << "\nСортировка станков по мощности (возрастание):\n";
    std::sort(machineContainer.begin(), machineContainer.end(), compareMachinePower);
    for (const auto& m : machineContainer) {
        std::cout << "  " << m->getModel() << " -> " << m->getPower() << " кВт\n";
    }

    if (machineContainer.getSize() > 0) {
        auto maxIt = std::max_element(machineContainer.begin(), machineContainer.end(),
            [](const Machine* a, const Machine* b) {
                return a->getPower() < b->getPower();
            });
        std::cout << "\nСамый мощный станок:\n";
        printMachineInfo(*(*maxIt));
    }

    std::cout << "\n--- 2. Контейнер MyContainer<Human*> (работники) ---\n";

    MyContainer<Human*> humanContainer;

    humanContainer.push_back(new Worker("Иван Петров", 32, 1001, 8));
    humanContainer.push_back(new Worker("Сергей Сидоров", 28, 1002, 5));
    humanContainer.push_back(new Accountant("Елена Смирнова", 41, 2001, "Расчётный"));
    humanContainer.push_back(new Worker("Анна Кузнецова", 35, 1004, 10));

    std::cout << "Добавлено работников: " << humanContainer.getSize() << "\n\n";

    std::cout << "Список работников:\n";
    for (const auto& h : humanContainer) {
        printHumanInfo(*h);
    }

    std::cout << "\nПоиск сотрудника по имени 'Сергей Сидоров':\n";
    auto humanIt = std::find_if(humanContainer.begin(), humanContainer.end(),
                                FindHumanByName("Сергей Сидоров"));
    if (humanIt != humanContainer.end()) {
        std::cout << "  Найден: ";
        printHumanInfo(*(*humanIt));
    }

    std::cout << "\nСортировка работников по возрасту:\n";
    std::sort(humanContainer.begin(), humanContainer.end(), compareWorkerAge);
    for (const auto& h : humanContainer) {
        std::cout << "  " << h->getName() << ", возраст: " << h->getAge() << " лет\n";
    }

    std::cout << "\n--- 3. Контейнер с простыми типами ---\n";

    MyContainer<int> numbers;
    numbers.push_back(10);
    numbers.push_back(5);
    numbers.push_back(8);
    numbers.push_back(3);

    std::cout << "Числа до сортировки: ";
    for (const auto& n : numbers) std::cout << n << " ";
    std::cout << std::endl;

    std::sort(numbers.begin(), numbers.end());
    std::cout << "Числа после сортировки: ";
    for (const auto& n : numbers) std::cout << n << " ";
    std::cout << std::endl;

    for (auto it = machineContainer.begin(); it != machineContainer.end(); ++it) {
        delete *it;
    }

    for (auto it = humanContainer.begin(); it != humanContainer.end(); ++it) {
        delete *it;
    }

    return 0;
}
