#ifndef LATHE_H
#define LATHE_H

#include "Machine.h"

class Lathe : public Machine {
private:
    double maxDiameter;

public:
    Lathe(const std::string& model, int power, double maxDiameter);
    
    void process() override;
    double getMaxDiameter() const;
};

#endif
