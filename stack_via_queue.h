#pragma once

#include <queue>
#include <cstddef>

template <typename T>
class MyStack {
public:
    
    void push(T x) {
        q.push(x);
        for (size_t i = 1; i < q.size(); ++i) {
            q.push(q.front());
            q.pop();
        }
    }
    
    T pop() {
        T x = q.front();
        q.pop();
        return x;
    }
    
    T top() {
        return q.front();
    }
    
    bool empty() {
        return q.empty();
    }
private:
    std::queue<T> q;
};
