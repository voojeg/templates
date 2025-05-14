#include <stack>

template <class T>
class CircularQueue {
public:
  CircularQueue(size_t size) : size_(size) {}

  bool EnQueue(T value) {
    if (!IsFull()) {
      if (s1_.empty()) {
        front_ = value;
      }
      s1_.push(value);
      back_ = value;
      return true;
    }
    return false;
  }

  bool DeQueue() {
    if (!IsEmpty()) {
      if (s2_.empty()) {
        back_ = s1_.top();
        while (!s1_.empty()) {
          s2_.push(s1_.top());
          s1_.pop();
        }
      }
      s2_.pop();
      return true;
    }
    return false;
  }

  T Front() const {
    if (!IsEmpty() && !s2_.empty()) {
      return s2_.top();
    }
    if (!s2_.empty()) {
      return front_;
    }
  }

  T Rear() const {
    if (!IsEmpty()) {
      return back_;
    }
  }

  bool IsEmpty() const {
    return s1_.empty() && s2_.empty();
  }

  bool IsFull() const {
    return s1_.size() + s2_.size() == size_;
  }

private:
  size_t size_;
  T front_, back_;
  std::stack<T> s1_, s2_;
};

