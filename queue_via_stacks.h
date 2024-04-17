#pragma once

#include <stack>

template <typename T>
class MyQueue {
public:
    
    void push(int x) {
        if (s1.empty()) front = x;
        s1.push(x);
    }
    
    T pop() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        T tmp = s2.top();
        s2.pop();
        return tmp;
    }
    
    T peek() {
        if (!s2.empty()) return s2.top();
        return front;
    }
    
    bool empty() {
        return s1.empty() && s2.empty();
    }
    
private:
    std::stack<T> s1, s2;
    T front;
};
