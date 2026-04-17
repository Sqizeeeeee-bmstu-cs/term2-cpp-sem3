#include "MachineContainer.h"
#include "Machine.h"

MachineContainer::MachineContainer() 
    : data(nullptr), size(0), capacity(0) {}

MachineContainer::~MachineContainer() {
    delete[] data;
}

void MachineContainer::resize(size_t new_capacity) {
    Machine** new_data = new Machine*[new_capacity];
    for (size_t i = 0; i < size; ++i) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

size_t MachineContainer::getSize() const { return size; }
size_t MachineContainer::getCapacity() const { return capacity; }

void MachineContainer::push_back(Machine* machine) {
    if (size >= capacity) {
        size_t new_cap = (capacity == 0) ? 1 : capacity * 2;
        resize(new_cap);
    }
    data[size++] = machine;
}

void MachineContainer::pop_back() {
    if (size > 0) --size;
}

Machine* MachineContainer::operator[](size_t index) const {
    return data[index];
}

MachineContainer::Iterator MachineContainer::begin() {
    return Iterator(data);
}

MachineContainer::Iterator MachineContainer::end() {
    return Iterator(data + size);
}
