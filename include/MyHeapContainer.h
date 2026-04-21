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
    
    T& getElementAt(size_t index) {
        if (index < buffer_count) {
            return buffer[index];
        } else {
            return heap[index - buffer_count];
        }
    }
    
    const T& getElementAt(size_t index) const {
        if (index < buffer_count) {
            return buffer[index];
        } else {
            return heap[index - buffer_count];
        }
    }

public:
    MyHeapContainer() : buffer_count(0), total_size(0) {}
    
    ~MyHeapContainer() {}

    size_t getSize() const {
        return total_size;
    }

    size_t getCapacity() const {
        return BUFFER_SIZE + heap.capacity();
    }

    void push_back(const T& value) {
        if (buffer_count < BUFFER_SIZE) {
            buffer[buffer_count++] = value;
        } else {
            flushBufferToHeap();
            buffer[buffer_count++] = value;
        }
        total_size++;
    }

    void pop_back() {
        if (buffer_count == 0) return;
        
        buffer_count--;
        total_size--;
    }

    T& operator[](size_t index) {
        return getElementAt(index);
    }

    const T& operator[](size_t index) const {
        return getElementAt(index);
    }

    class Iterator {
    private:
        MyHeapContainer* container;
        size_t current_pos;
        
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(MyHeapContainer* cont = nullptr, size_t pos = 0) 
            : container(cont), current_pos(pos) {}
        
        reference operator*() const {
            return container->getElementAt(current_pos);
        }

        pointer operator->() const {
            return &(container->getElementAt(current_pos));
        }

        Iterator& operator++() {
            ++current_pos;
            return *this;
        }

        Iterator operator++(int) {
            Iterator old = *this;
            ++current_pos;
            return old;
        }

        Iterator& operator--() {
            --current_pos;
            return *this;
        }

        Iterator operator--(int) {
            Iterator old = *this;
            --current_pos;
            return old;
        }

        // Арифметика
        Iterator operator+(difference_type n) const {
            return Iterator(container, current_pos + n);
        }

        Iterator operator-(difference_type n) const {
            return Iterator(container, current_pos - n);
        }

        difference_type operator-(const Iterator& other) const {
            return current_pos - other.current_pos;
        }

        Iterator& operator+=(difference_type n) {
            current_pos += n;
            return *this;
        }

        Iterator& operator-=(difference_type n) {
            current_pos -= n;
            return *this;
        }

        reference operator[](difference_type n) const {
            return container->getElementAt(current_pos + n);
        }

        // Сравнение
        bool operator==(const Iterator& other) const {
            return container == other.container && current_pos == other.current_pos;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

        bool operator<(const Iterator& other) const {
            return current_pos < other.current_pos;
        }

        bool operator>(const Iterator& other) const {
            return current_pos > other.current_pos;
        }

        bool operator<=(const Iterator& other) const {
            return current_pos <= other.current_pos;
        }

        bool operator>=(const Iterator& other) const {
            return current_pos >= other.current_pos;
        }
    };

    Iterator begin() {
        return Iterator(this, 0);
    }

    Iterator end() {
        return Iterator(this, total_size);
    }

    Iterator begin() const {
        return Iterator(const_cast<MyHeapContainer*>(this), 0);
    }

    Iterator end() const {
        return Iterator(const_cast<MyHeapContainer*>(this), total_size);
    }
};

#endif