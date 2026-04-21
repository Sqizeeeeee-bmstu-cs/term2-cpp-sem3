#ifndef MYHEAPCONTAINER_H
#define MYHEAPCONTAINER_H

#include <cstddef>
#include <vector>
#include <algorithm>
#include <iterator>

template <typename T>
class MyHeapContainer {
private:
    static const size_t BUFFER_SIZE = 5;
    T buffer[BUFFER_SIZE];
    size_t buffer_count;
    
    std::vector<T> heap;
    
    size_t total_size;
    
    void flushBufferToHeap() {
        for (int i = 0; i < buffer_count; i++){
            heap.push_back(buffer[i]);
        }

        buffer_count = 0;
        std::make_heap(heap.begin(), heap.end());

    }
    
    // Получить элемент по глобальному индексу (из буфера или heap)
    T& getElementAt(size_t index) {
        
        if (index < buffer_count){
            return buffer[index];
        } else {
            return heap[index - buffer_index]
        }

    }
    
    const T& getElementAt(size_t index) const {
        if (index < buffer_count){
            return buffer[index];
        } else {
            return heap[index - buffer_index]
        }
    }

public:
    MyContainer() : buffer_count(0), total_size(0) {}
    
    ~MyContainer() {}

    size_t getSize() const {
        return total_size;
    }

    size_t getCapacity() const {
        return BUFFER_SIZE + heap.capacity();
    }

    void push_back(const T& value) {
        if (buffer_count < BUFFER_SIZE){
            buffer[buffer_size++] = value;
        } else {
            flushBufferToHeap();
            buffer[buffer_count++] = value;
        }

        total_size++;
    }

    void pop_back() {
        if (total_size == 0) return;
        
        buffer_count--;
        total_size--;
    }

    T& operator[](size_t index) {
        return getElementAt(index);
    }

    const T& operator[](size_t index) const {
        return getElementAt(index);
    }

    // ===== ИТЕРАТОР =====
    class Iterator {
    private:
        // TODO: как хранить позицию в двух структурах?
        // Вариант: хранить индекс в общей логической последовательности
        MyContainer* container;
        size_t current_pos;  // позиция в общем облике [0, total_size)
        
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(MyContainer* cont = nullptr, size_t pos = 0) 
            : container(cont), current_pos(pos) {}
        
        // TODO: реализовать все операторы

        reference operator*() const {
            // TODO: используй container->getElementAt(current_pos)
        }

        pointer operator->() const {
            // TODO
        }

        Iterator& operator++() {
            // TODO
        }

        Iterator operator++(int) {
            // TODO
        }

        Iterator& operator--() {
            // TODO
        }

        Iterator operator--(int) {
            // TODO
        }

        Iterator operator+(difference_type n) const {
            // TODO
        }

        Iterator operator-(difference_type n) const {
            // TODO
        }

        difference_type operator-(const Iterator& other) const {
            // TODO
        }

        Iterator& operator+=(difference_type n) {
            // TODO
        }

        Iterator& operator-=(difference_type n) {
            // TODO
        }

        reference operator[](difference_type n) const {
            // TODO
        }

        bool operator==(const Iterator& other) const {
            // TODO
        }

        bool operator!=(const Iterator& other) const {
            // TODO
        }

        bool operator<(const Iterator& other) const {
            // TODO
        }

        bool operator>(const Iterator& other) const {
            // TODO
        }

        bool operator<=(const Iterator& other) const {
            // TODO
        }

        bool operator>=(const Iterator& other) const {
            // TODO
        }
    };

    Iterator begin() {
        // TODO: возвращаем итератор с pos=0
    }

    Iterator end() {
        // TODO: возвращаем итератор с pos=total_size
    }
    
    Iterator begin() const {
        // TODO: const версия
    }

    Iterator end() const {
        // TODO: const версия
    }
};

#endif