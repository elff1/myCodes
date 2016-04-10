#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class IntIndex {
public:
  IntIndex(int d, int i) : data(d), index(i) {}
  int data, index;
};

class Solution {
public:
  vector<int> twoSum(vector<int> &nums, int target) {
    vector<IntIndex> numIndexs;
    for (auto it = nums.begin(); it != nums.end(); ++it)
      numIndexs.push_back(IntIndex(*it, it - nums.begin() + 1));
    
    sort(numIndexs.begin(), numIndexs.end(),
          [] (const IntIndex &a, const IntIndex &b)
            { return a.data < b.data;});
    
    auto beg = numIndexs.begin(), end = numIndexs.end() - 1;
    int sum;
    while (beg < end)
    {
      sum = beg->data + end->data;
      if (sum == target)
        break;
      if (sum < target)
        ++beg;
      if (target < sum)
        --end;
    }
    
    auto i1 = beg->index, i2 = end->index;
    if (i1 > i2)
      swap(i1, i2);
    return vector<int>{i1, i2}; //{(int)(beg - nums.begin()) + 1, (int)(end - nums.begin()) + 1};
  }
};

int main()
{
  vector<int> nums = {16, 7, 1, 15};
  int target = 8;
  Solution s;
  auto ans = s.twoSum(nums, target);
  for (auto a : ans)
    cout << a << " ";
  cout << endl;
  return 0;
}