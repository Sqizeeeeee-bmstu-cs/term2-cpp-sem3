#include "MachineContainer.h"
#include "Lathe.h"
#include "Milling.h"
#include "Grinding.h"
#include <iostream>
#include <algorithm>
#include <string>

// Функция для вывода информации о станке
void printMachineInfo(const Machine& machine) {
    std::cout << "Тип: " << machine.getType() 
              << ", Модель: " << machine.getModel()
              << ", Мощность: " << machine.getPower() << " кВт" << std::endl;
}

// Компаратор для сортировки по мощности (по возрастанию)
bool compareByPower(const Machine* a, const Machine* b) {
    return a->getPower() < b->getPower();
}

// Компаратор для сортировки по модели (по алфавиту)
bool compareByModel(const Machine* a, const Machine* b) {
    return a->getModel() < b->getModel();
}

// Предикат для поиска станка по модели
struct FindByModel {
    std::string targetModel;
    FindByModel(const std::string& model) : targetModel(model) {}
    bool operator()(const Machine* machine) const {
        return machine->getModel() == targetModel;
    }
};

int main() {
    std::cout << "=== Демонстрация MachineContainer ===\n\n";

    // Создаём контейнер
    MachineContainer container;

    // Добавляем станки
    container.push_back(new Lathe("16K20", 11, 400));
    container.push_back(new Milling("6R12", 7, 1600));
    container.push_back(new Lathe("1K62", 10, 300));
    container.push_back(new Grinding("3M174", 5, 0.002));
    container.push_back(new Milling("VM-1", 4, 12000));
    container.push_back(new Lathe("DL-20", 15, 500));

    std::cout << "Всего станков: " << container.getSize() << "\n\n";

    // 1. Перебор с помощью итераторов
    std::cout << "--- Перебор станков (через итераторы) ---\n";
    for (auto it = container.begin(); it != container.end(); ++it) {
        printMachineInfo(*(*it));  // (*it) -> Machine*, ещё одна разыменовка
    }
    std::cout << std::endl;

    // 2. Диапазонный for (работает благодаря begin/end)
    std::cout << "--- Диапазонный for ---\n";
    for (const auto& machinePtr : container) {
        printMachineInfo(*machinePtr);
    }
    std::cout << std::endl;

    // 3. Поиск станка по модели с помощью std::find_if
    std::string searchModel = "1K62";
    auto it = std::find_if(container.begin(), container.end(), 
                           FindByModel(searchModel));
    
    if (it != container.end()) {
        std::cout << "Найден станок с моделью " << searchModel << ": ";
        printMachineInfo(*(*it));
    } else {
        std::cout << "Станок с моделью " << searchModel << " не найден\n";
    }
    std::cout << std::endl;

    // 4. Сортировка по мощности
    std::cout << "--- Сортировка по мощности (возрастание) ---\n";
    std::sort(container.begin(), container.end(), compareByPower);
    
    for (const auto& machinePtr : container) {
        std::cout << machinePtr->getModel() 
                  << " -> " << machinePtr->getPower() << " кВт\n";
    }
    std::cout << std::endl;

    // 5. Сортировка по модели
    std::cout << "--- Сортировка по модели (алфавит) ---\n";
    std::sort(container.begin(), container.end(), compareByModel);
    
    for (const auto& machinePtr : container) {
        std::cout << machinePtr->getModel() << std::endl;
    }
    std::cout << std::endl;

    // 6. Реальная задача: найти все станки с мощностью больше 10 кВт
    std::cout << "--- Станки с мощностью > 10 кВт ---\n";
    for (const auto& machinePtr : container) {
        if (machinePtr->getPower() > 10) {
            printMachineInfo(*machinePtr);
        }
    }

    // 7. Реальная задача: найти самый мощный станок
    if (container.getSize() > 0) {
        auto maxPowerIt = std::max_element(container.begin(), container.end(),
            [](const Machine* a, const Machine* b) {
                return a->getPower() < b->getPower();
            });
        
        std::cout << "\n--- Самый мощный станок ---\n";
        printMachineInfo(*(*maxPowerIt));
    }

    // 8. Реальная задача: средняя мощность станков
    if (container.getSize() > 0) {
        double totalPower = 0;
        for (const auto& machinePtr : container) {
            totalPower += machinePtr->getPower();
        }
        double avgPower = totalPower / container.getSize();
        std::cout << "\n--- Средняя мощность станков: " << avgPower << " кВт ---\n";
    }

    // Освобождение памяти (контейнер не удаляет станки, удаляем вручную)
    for (auto it = container.begin(); it != container.end(); ++it) {
        delete *it;
    }

    std::cout << "\n=== Программа завершена ===\n";
    return 0;
}