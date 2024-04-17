#pragma once

#include <stack>
#include <cstddef>

template <typename T>
class MyCircularQueue {
public:
    MyCircularQueue() = delete;

    MyCircularQueue(size_t k) {
        size = k;
    }
    
    bool enQueue(int value) {
        if (!isFull()) {
            if (s1.empty()) front = value;
            s1.push(value);
            back = value;
            return true;
        }
        return false;
    }
    
    bool deQueue() {
        if (!isEmpty()) {
            if (s2.empty()) {
                back = s1.top();
                while (!s1.empty()) {
                    s2.push(s1.top());
                    s1.pop();
                }
            }
            s2.pop();
            return true;
        }
        return false;
    }
    
    int Front() const {
        if (!isEmpty() && !s2.empty()) return s2.top();
        if (!s2.empty()) return front;
    }
    
    int Rear() const {
        if (!isEmpty()) return back;
    }
    
    bool isEmpty() const {
        return s1.empty() && s2.empty();
    }
    
    bool isFull() const {
        return s1.size() + s2.size() == size;
    }
private:
    std::stack<T> s1, s2;
    T front, back;
    size_t size;
};
