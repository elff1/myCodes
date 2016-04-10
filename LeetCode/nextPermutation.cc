#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
  void nextPermutation(vector<int> &nums) {
    if (nums.empty())
      return;
    
    auto iter = nums.end() - 1;
    for (; iter != nums.begin(); --iter) {
      if (*iter > *(iter - 1)) {
        auto popIter = nums.end() - 1;
        for (; *popIter <= *(iter - 1); --popIter);
        
        iter_swap(iter - 1, popIter);
        break;
      }
    }
    
    reverse(iter, nums.end());
  }
};

int main()
{
  Solution s;
  vector<vector<int>> data = {
    {1, 2, 3},
    {3, 2, 1},
    {1, 1, 5},
    {3, 2, 4, 3, 2, 1, 1}
  };
  
  for (auto d : data) {
    s.nextPermutation(d);
    
    for (auto n : d)
      cout << n << ' ';
    cout << endl;
  }
  
  return 0;
}