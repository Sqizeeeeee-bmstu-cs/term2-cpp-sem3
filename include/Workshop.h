#ifndef WORKSHOP_H
#define WORKSHOP_H

#include <string>
#include <vector>
#include <memory>

class Machine;

class Workshop {
private:
    std::string name;
    std::vector<std::unique_ptr<Machine>> machines;

public:
    explicit Workshop(const std::string& name);
    ~Workshop() = default;

    std::string getName() const;

    void addMachine(Machine* machine);
    const std::vector<std::unique_ptr<Machine>>& getMachines() const;

    void showMachines() const;
};

#endif
