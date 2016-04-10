#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int firstMissingPositive(vector<int> &nums) {
    int n = nums.size();
    int tmp = 0;
    for (auto num : nums) {
      while (num > 0 && num <= n) {
        if (num == nums[num - 1])
          break;
        tmp = move(nums[num - 1]);
        nums[num - 1] = move(num);
        num = move(tmp);
      }
    }
    
    int i = 0;
    for (; i < n; ++i)
      if (nums[i] != i + 1)
        break;
    
    return i + 1;
  }
};

int main()
{
  Solution s;
  vector<vector<int>> data = {
    {2, 4, 6, 8, 10, 9, 7, 5, 3, 1},
    {3, 4, -1, 1}
  };
  
  for (auto d : data)
    cout << s.firstMissingPositive(d) << endl;
  
  return 0;
}