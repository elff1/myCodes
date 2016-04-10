#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int searchInsert(vector<int> nums, int target) {
    auto head = nums.begin();
    auto tail = nums.end();
    decltype(nums.begin()) mid;
    
    while(head < tail) {
      mid = head + ((tail - head) >> 1);
      if (*mid == target) return mid - nums.begin();
      if (target < *mid)
        tail = mid;
      else
        head = mid + 1;
    }
    
    return head - nums.begin();
  }
};

int main() {
  Solution s;
  vector<int> nums = {1, 3, 5, 6};
  vector<int> targets = {5, 2, 7, 0};
  
  for (auto n : targets)
    cout << s.searchInsert(nums, n) << ' ';
  
  cout << endl;
}