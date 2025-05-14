#include <vector>

class DisjointSet {
public:
    DisjointSet() = delete;

    explicit DisjointSet(size_t n) {
        data_.resize(n);
        for (size_t i = 0; i != n; ++i) {
            data_[i] = {i, 0};
        }
    }

    size_t Find(size_t i) {
        if (i != data_[i].parent) {
            data_[i].parent = Find(data_[i].parent);
        }
        return data_[i].parent;
    }

    void Union(size_t i, size_t j) {
        i = Find(i);
        j = Find(j);
        if (i == j) {
            return;
        }
        if (data_[i].rank == data_[j].rank) {
            ++data_[i].rank;
        }
        if (data_[i].rank > data_[j].rank) {
            data_[j].parent = i;
        } else {
            data_[i].parent = j;
        }
    }
private:
    struct Node {
        size_t parent;
        int rank;
    };

    std::vector<Node> data_;
};

