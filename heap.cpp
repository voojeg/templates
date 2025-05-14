#include <vector>
#include <functional>

template <class T, class Compare = std::less<T>>
class BinaryHeap {
public:
    bool Empty() const {
        return heap_.empty();
    }
       
    void Insert(const T& val) {
        heap_.push_back(val);
        SiftUp(heap_.size() - 1);
    }
    
    T GetTop() const {
        if (!heap_.empty()) {
            return heap_.front();
        }
    }    
    
    void ExtractTop() {
        if (!heap_.empty()) {
            heap_.front() = heap_.back();
            heap_.pop_back();
            SiftDown(0);
        }
    }
private:
    std::vector<T> heap_;
    
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
        while (i > 0 && compare(heap_[Parent(i)], heap_[i])) {
            std::swap(heap_[Parent(i)], heap_[i]);
            i = Parent(i);
        }
    }
    
    void SiftDown(int i) {
        int index_of_max = i;
        int l = LeftChild(i);
        if (l < heap_.size() && compare(heap_[index_of_max], heap_[l])) {
            index_of_max = l;
        }
        int r = RightChild(i);
        if (r < heap_.size() && compare(heap_[index_of_max], heap_[r])) {
            index_of_max = r;
        }
        if (i != index_of_max) {
            std::swap(heap_[i], heap_[index_of_max]);
            SiftDown(index_of_max);
        }
    }
};

