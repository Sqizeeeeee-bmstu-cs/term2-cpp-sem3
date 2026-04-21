#include "MyHeapContainer.h"
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

int main() {
    std::cout << "=== Демонстрация шаблонного контейнера MyHeapContainer<T> ===\n\n";

    std::cout << "--- 1. Контейнер MyHeapContainer<Machine*> (станки) ---\n";

    MyHeapContainer<Machine*> machineContainer;

    std::cout << "Добавляем станки (заполняем буфер из 5 элементов):\n";
    machineContainer.push_back(new Lathe("16K20", 11, 400));
    std::cout << "  [+] Lathe 16K20 | Размер: " << machineContainer.getSize() << "\n";
    
    machineContainer.push_back(new Milling("6R12", 7, 1600));
    std::cout << "  [+] Milling 6R12 | Размер: " << machineContainer.getSize() << "\n";
    
    machineContainer.push_back(new Lathe("1K62", 10, 300));
    std::cout << "  [+] Lathe 1K62 | Размер: " << machineContainer.getSize() << "\n";
    
    machineContainer.push_back(new Grinding("3M174", 5, 0.002));
    std::cout << "  [+] Grinding 3M174 | Размер: " << machineContainer.getSize() << "\n";
    
    machineContainer.push_back(new Milling("VM-1", 4, 12000));
    std::cout << "  [+] Milling VM-1 | Размер: " << machineContainer.getSize() << " (БУФЕР ПОЛОН)\n";

    std::cout << "\nДобавляем ещё станки (происходит flush буфера в heap):\n";
    machineContainer.push_back(new Lathe("DIP-300", 8, 500));
    std::cout << "  [+] Lathe DIP-300 | Размер: " << machineContainer.getSize() << " (FLUSH!)\n";

    machineContainer.push_back(new Grinding("5E32", 6, 0.001));
    std::cout << "  [+] Grinding 5E32 | Размер: " << machineContainer.getSize() << "\n";

    std::cout << "\nВсе станки в контейнере:\n";
    for (size_t i = 0; i < machineContainer.getSize(); i++) {
        std::cout << "  [" << i << "] ";
        printMachineInfo(*machineContainer[i]);
    }

    std::cout << "\nПеребор через итератор (forward):\n";
    size_t idx = 0;
    for (auto it = machineContainer.begin(); it != machineContainer.end(); ++it) {
        std::cout << "  [" << idx++ << "] ";
        printMachineInfo(*(*it));
    }

    std::cout << "\nАрифметика итераторов (пример: begin() + 3):\n";
    auto it = machineContainer.begin() + 3;
    std::cout << "  Элемент на позиции 3: ";
    printMachineInfo(*(*it));

    std::cout << "\nРазница между итераторами:\n";
    auto it_end = machineContainer.end() - 1;
    std::cout << "  Расстояние от begin до end: " << (machineContainer.end() - machineContainer.begin()) << "\n";
    std::cout << "  Расстояние от begin до последнего: " << (it_end - machineContainer.begin()) << "\n";

    std::cout << "\nТестирование pop_back():\n";
    std::cout << "  Размер перед pop_back: " << machineContainer.getSize() << "\n";
    machineContainer.pop_back();
    std::cout << "  Размер после pop_back: " << machineContainer.getSize() << "\n";
    std::cout << "  Размер после второго pop_back: ";
    machineContainer.pop_back();
    std::cout << machineContainer.getSize() << "\n";

    std::cout << "\nОставшиеся станки после удалений:\n";
    for (size_t i = 0; i < machineContainer.getSize(); i++) {
        std::cout << "  [" << i << "] ";
        printMachineInfo(*machineContainer[i]);
    }

    std::cout << "\nИнформация о контейнере:\n";
    std::cout << "  Размер: " << machineContainer.getSize() << "\n";
    std::cout << "  Ёмкость: " << machineContainer.getCapacity() << "\n";

    std::cout << "\n--- 2. Контейнер MyHeapContainer<Human*> (работники) ---\n";

    MyHeapContainer<Human*> humanContainer;

    std::cout << "Добавляем работников:\n";
    humanContainer.push_back(new Worker("Иван Петров", 32, 1001, 8));
    std::cout << "  [+] Worker Иван Петров\n";
    
    humanContainer.push_back(new Worker("Сергей Сидоров", 28, 1002, 5));
    std::cout << "  [+] Worker Сергей Сидоров\n";
    
    humanContainer.push_back(new Accountant("Елена Смирнова", 41, 2001, "Расчётный"));
    std::cout << "  [+] Accountant Елена Смирнова\n";

    std::cout << "\nСписок работников:\n";
    for (size_t i = 0; i < humanContainer.getSize(); i++) {
        std::cout << "  [" << i << "] ";
        printHumanInfo(*humanContainer[i]);
    }

    std::cout << "\n--- 3. Контейнер с простыми типами (int) ---\n";

    MyHeapContainer<int> numbers;

    std::cout << "Добавляем числа:\n";
    for (int val : {42, 17, 99, 5, 31, 88, 12}) {
        numbers.push_back(val);
        std::cout << "  [+] " << val << " | Размер: " << numbers.getSize() << "\n";
    }

    std::cout << "\nЧисла в порядке добавления:\n";
    std::cout << "  ";
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::cout << "\nДоступ по индексу:\n";
    for (size_t i = 0; i < numbers.getSize(); i++) {
        std::cout << "  numbers[" << i << "] = " << numbers[i] << "\n";
    }

    std::cout << "\nУдаляем последние 2 числа:\n";
    std::cout << "  Было: ";
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    numbers.pop_back();
    numbers.pop_back();
    std::cout << "  Стало: ";
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Очистка
    for (auto it = machineContainer.begin(); it != machineContainer.end(); ++it) {
        delete *it;
    }
    for (auto it = humanContainer.begin(); it != humanContainer.end(); ++it) {
        delete *it;
    }

    std::cout << "\n=== Тестирование завершено успешно! ===\n";

    return 0;
}