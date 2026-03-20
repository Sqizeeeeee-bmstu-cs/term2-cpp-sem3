#ifndef GRINDING_H
#define GRINDING_H

#include "Machine.h"

class Grinding : public Machine {
private:
    double precision;

public:
    Grinding(const std::string& model, int power, double precision);
    
    void process() override;
    double getPrecision() const;
};

#endif
