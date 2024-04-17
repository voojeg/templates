#include <iostream>
#include <vector>
#include <queue>

void BalanceQueues(std::priority_queue<int>& smaller,
                   std::priority_queue<int, std::vector<int>, std::greater<int>>& larger) {
  if (larger.size() > smaller.size()) {
    smaller.push(larger.top());
    larger.pop();
  } else {
    larger.push(smaller.top());
    smaller.pop();
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> nums[i];
  }
  std::priority_queue<int> smaller;
  std::priority_queue<int, std::vector<int>, std::greater<int>> larger;
  long long res = 0;
  for (int num : nums) {
    if (!larger.empty() && num >= larger.top()) {
      larger.push(num);
    } else {
      smaller.push(num);
    }
    BalanceQueues(smaller, larger);
    if (larger.size() > smaller.size()) {
      res += larger.top();
    } else {
      res += smaller.top();
    }
  }
  std::cout << res;
  return 0;
}
