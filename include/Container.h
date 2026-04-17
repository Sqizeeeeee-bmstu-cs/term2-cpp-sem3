#ifndef MYCONTAINER_H
#define MYCONTAINER_H

#include <cstddef>
#include <iterator>

template <typename T>
class MyContainer {
private:
    T* data;
    size_t size;
    size_t capacity;

    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    MyContainer() : data(nullptr), size(0), capacity(0) {}
    
    ~MyContainer() {
        delete[] data;
    }

    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }

    void push_back(const T& value) {
        if (size >= capacity) {
            size_t new_cap = (capacity == 0) ? 1 : capacity * 2;
            resize(new_cap);
        }
        data[size++] = value;
    }

    void pop_back() {
        if (size > 0) --size;
    }

    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    class Iterator {
    private:
        T* ptr;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(T* p = nullptr) : ptr(p) {}
        
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

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + size); }
    
    Iterator begin() const { return Iterator(data); }
    Iterator end() const { return Iterator(data + size); }
};

#endif
