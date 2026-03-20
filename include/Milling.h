#ifndef MILLING_H
#define MILLING_H

#include "Machine.h"

class Milling : public Machine {
private:
    int spindleSpeed;

public:
    Milling(const std::string& model, int power, int spindleSpeed);
    
    void process() override;
    int getSpindleSpeed() const;
};

#endif
