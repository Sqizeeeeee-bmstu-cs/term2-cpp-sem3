#include <iostream>
#include <memory>
#include <vector>
#include <typeinfo>


#include "Human.h"
#include "Worker.h"
#include "Accountant.h"
#include "Master.h"
#include "Machine.h"
#include "Lathe.h"
#include "Milling.h"
#include "Grinding.h"
#include "Workshop.h"
#include "Factory.h"

void demonstratePolymorphism(Machine& machine) {
    std::cout << "Тип станка: " << machine.getType() << std::endl;
    std::cout << "Модель: " << machine.getModel() << std::endl;
    std::cout << "Мощность: " << machine.getPower() << " кВт" << std::endl;
    std::cout << "Выполнение работы: ";
    machine.process();
    std::cout << std::endl;
}

int main() {
    std::cout << "=== Система управления заводом ===\n\n";

    // Создаём завод
    Factory factory("ТехМаш");

    // Создаём работников (агрегация — живут отдельно от завода)
    Worker* worker1 = new Worker("Иван Петров", 32, 1001, 8);
    Worker* worker2 = new Worker("Сергей Сидоров", 28, 1002, 5);
    Accountant* accountant = new Accountant("Елена Смирнова", 41, 2001, "Расчётный");
    Master* master = new Master("Алексей Кузнецов", 45, 3001);

    // Нанимаем работников
    factory.hireWorker(worker1);
    factory.hireWorker(worker2);
    factory.hireWorker(accountant);
    factory.hireWorker(master);

    // Добавляем рабочих в бригаду мастера (агрегация)
    master->addWorker(worker1);
    master->addWorker(worker2);

    // Создаём цеха (композиция — создаются внутри завода)
    factory.addWorkshop("Механический цех №1");
    factory.addWorkshop("Прецизионный цех");

    // Получаем цеха и добавляем станки (композиция — станки внутри цеха)
    Workshop* workshop1 = factory.getWorkshop("Механический цех №1");
    if (workshop1) {
        workshop1->addMachine(new Lathe("16К20", 11, 400));
        workshop1->addMachine(new Milling("6Р12", 7, 1600));
        workshop1->addMachine(new Lathe("1К62", 10, 300));
    }

    Workshop* workshop2 = factory.getWorkshop("Прецизионный цех");
    if (workshop2) {
        workshop2->addMachine(new Grinding("3М174", 5, 0.002));
        workshop2->addMachine(new Milling("VM-1", 4, 12000));
    }

    // Ассоциация: привязываем рабочих к станкам
    if (workshop1) {
        auto& machines = workshop1->getMachines();
        if (machines.size() >= 2) {
            worker1->assignMachine(machines[0].get());  // первый токарный
            worker2->assignMachine(machines[1].get());  // фрезерный
        }
    }

    // Демонстрация работы
    std::cout << "\n--- Информация о заводе ---\n";
    factory.showInfo();

    std::cout << "\n--- Работа сотрудников ---\n";
    worker1->work();   // токарный станок
    worker2->work();   // фрезерный
    accountant->work();
    master->work();

    std::cout << "\n--- Рабочий без станка ---\n";
    Worker* tempWorker = new Worker("Василий Зайцев", 25, 1003, 1);
    tempWorker->work();  // не закреплён за станком
    delete tempWorker;

    std::cout << "\n--- Увольнение работника ---\n";
    factory.fireWorker(1002);  // увольняем Сергея
    factory.showInfo();

    Lathe lathe("16K20", 11, 400);
    Milling milling("6R12", 7, 1600);
    Grinding grinding("3M174", 5, 0.002);

    demonstratePolymorphism(lathe);
    demonstratePolymorphism(milling);
    demonstratePolymorphism(grinding);

    std::vector<std::unique_ptr<Machine>> machines;

    machines.push_back(std::make_unique<Lathe>("УмныйТокарь", 15, 500));
    machines.push_back(std::make_unique<Milling>("УмнаяФреза", 10, 3000));
    machines.push_back(std::make_unique<Grinding>("УмныйШлифовщик", 8, 0.0005));

    std::cout << "\n--- Полиморфный контейнер станков ---\n";
    for (const auto& m : machines) {
        demonstratePolymorphism(*m);
    }

    std::cout << "\n--- Демонстрация dynamic_cast и typeid ---\n";
    for (const auto& m : machines) {
        std::cout << "Фактический тип: " << typeid(*m).name() << std::endl;
        
        if (auto lathe = dynamic_cast<Lathe*>(m.get())) {
            std::cout << "  Это токарный станок, макс. диаметр: " << lathe->getMaxDiameter() << " мм" << std::endl;
        } else if (auto milling = dynamic_cast<Milling*>(m.get())) {
            std::cout << "  Это фрезерный станок, обороты: " << milling->getSpindleSpeed() << " об/мин" << std::endl;
        } else if (auto grinding = dynamic_cast<Grinding*>(m.get())) {
            std::cout << "  Это шлифовальный станок, точность: " << grinding->getPrecision() << " мм" << std::endl;
        }
    }

    // Освобождение памяти (агрегация — удаляем вручную)
    delete worker1;
    delete worker2;
    delete accountant;
    delete master;

    std::cout << "\n=== Программа завершена ===\n";
    return 0;
}
