#include <unordered_map>
#include <memory>
#include <vector>

template <typename T>
class Trie {
public:
    Trie() {
        root_ = std::make_unique<Node>();
    }
    
    void Insert(const std::vector<T>& word) {
        auto tmp = root_.get();
        for (int i = 0; i < word.size(); ++i) {
            const T c = word[i];
            if (!tmp->children[c - 'a']) {
                tmp->children[c - 'a'] = std::make_unique<Node>();
            }
            tmp = tmp->children[c - 'a'].get();
            if (i + 1 == word.size()) {
                tmp->isWord = true;
            }
        }
    }
    
    bool Search(const std::vector<T>& word) {
        auto tmp = root_.get();
        for (const T& c : word) {
            if (!tmp->children[c - 'a']) {
                return false;
            }
            tmp = tmp->children[c - 'a'].get();
        }
        return tmp->isWord;
    }
    
    bool StartsWith(const std::vector<T>& prefix) {
        auto tmp = root_.get();
        for (char c : prefix) {
            if (!tmp->children[c - 'a']) {
                return false;
            }
            tmp = tmp->children[c - 'a'].get();
        }
        return true;
    }
private:
    struct Node {
        std::unordered_map<T, std::unique_ptr<Node>> children;
        bool isWord = false;
    };
    std::unique_ptr<Node> root_;
};

