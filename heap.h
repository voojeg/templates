#pragma once

#include <vector>
#include <functional>

template <class T, class Compare = std::less<T>>
class BinaryHeap {
public:
    BinaryHeap() = default;
       
    bool Empty() const {
        return heap.empty();
    }
       
    void Insert(const T& val) {
        heap.push_back(val);
        SiftUp(heap.size() - 1);
    }
    
    T GetTop() const {
        if (!heap.empty()) {
            return heap[0];
        }
    }    
    
    void ExtractTop() {
        if (!heap.empty()) {
            heap[0] = heap[heap.size() - 1];
            heap.pop_back();
            SiftDown(0);
        }
    }
private:
    std::vector<T> heap;
    
    bool compare(const T& lhs, const T& rhs) const {
        return Compare()(lhs, rhs);
    }
        
    int Parent(int i) const {
        return (i - 1) / 2;
    }
    
    int LeftChild(int i) const {
        return 2 * i + 1;
    }
   
    int RightChild(int i) const {
        return 2 * i + 2;
    }
   
    void SiftUp(int i) {
        while (i > 0 && compare(heap[Parent(i)], heap[i])) {
            std::swap(heap[Parent(i)], heap[i]);
            i = Parent(i);
        }
    }
    
    void SiftDown(int i) {
        int index_of_max = i;
        int l = LeftChild(i);
        if (l < heap.size() && compare(heap[index_of_max], heap[l])) {
            index_of_max = l;
        }
        int r = RightChild(i);
        if (r < heap.size() && compare(heap[index_of_max], heap[r])) {
            index_of_max = r;
        }
        if (i != index_of_max) {
            std::swap(heap[i], heap[index_of_max]);
            SiftDown(index_of_max);
        }
    }
};
