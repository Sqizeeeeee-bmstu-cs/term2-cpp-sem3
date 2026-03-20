#ifndef MACHINE_H
#define MACHINE_H

#include <string>

class Machine {
private:
    std::string model;
    int power;
    bool isWorking;

public:
    Machine(const std::string& model, int power);
    virtual ~Machine() = default;

    std::string getModel() const;
    int getPower() const;
    bool getIsWorking() const;

    void start();
    void stop();

    virtual void process() = 0;
};

#endif
