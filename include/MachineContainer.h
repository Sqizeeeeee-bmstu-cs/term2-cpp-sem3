#ifndef MACHINECONTAINER_H
#define MACHINECONTAINER_H

#include <cstddef>
#include <iterator>

class Machine;

class MachineContainer {
private:
    Machine** data;
    size_t size;
    size_t capacity;

    void resize(size_t new_capacity);

public:
    MachineContainer();
    ~MachineContainer();

    size_t getSize() const;
    size_t getCapacity() const;

    void push_back(Machine* machine);
    void pop_back();

    Machine* operator[](size_t index) const;

    class Iterator {
    private:
        Machine** ptr;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = Machine*;
        using difference_type = std::ptrdiff_t;
        using pointer = Machine**;
        using reference = Machine*&;

        Iterator(Machine** p = nullptr) : ptr(p) {}
        
        reference operator*() const { return *ptr; }
        pointer operator->() const { return ptr; }
        
        Iterator& operator++() { ++ptr; return *this; }
        Iterator operator++(int) { Iterator old = *this; ++ptr; return old; }
        Iterator& operator--() { --ptr; return *this; }
        Iterator operator--(int) { Iterator old = *this; --ptr; return old; }
        
        Iterator operator+(difference_type n) const { return Iterator(ptr + n); }
        Iterator operator-(difference_type n) const { return Iterator(ptr - n); }
        difference_type operator-(const Iterator& other) const { return ptr - other.ptr; }
        
        Iterator& operator+=(difference_type n) { ptr += n; return *this; }
        Iterator& operator-=(difference_type n) { ptr -= n; return *this; }
        
        reference operator[](difference_type n) const { return *(ptr + n); }
        
        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
        bool operator<(const Iterator& other) const { return ptr < other.ptr; }
        bool operator>(const Iterator& other) const { return ptr > other.ptr; }
        bool operator<=(const Iterator& other) const { return ptr <= other.ptr; }
        bool operator>=(const Iterator& other) const { return ptr >= other.ptr; }
    };

    Iterator begin();
    Iterator end();
    
    Iterator begin() const { return Iterator(data); }
    Iterator end() const { return Iterator(data + size); }
};

#endif