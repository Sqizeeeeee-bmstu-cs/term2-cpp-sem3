#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <vector>
#include <memory>

class Human;
class Workshop;

class Factory {
private:
    std::string name;
    std::vector<std::unique_ptr<Workshop>> workshops;
    std::vector<Human*> workers;

public:
    explicit Factory(const std::string& name);

    std::string getName() const;

    void addWorkshop(const std::string& workshopName);
    Workshop* getWorkshop(const std::string& name) const;
    const std::vector<std::unique_ptr<Workshop>>& getWorkshops() const;

    void hireWorker(Human* worker);
    void fireWorker(int id);
    const std::vector<Human*>& getWorkers() const;

    void showInfo() const;
};

#endif