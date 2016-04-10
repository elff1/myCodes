#include <iostream>
#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
  int search(vector<int> &nums, int target) {
    if (nums.empty())
      return -1;
    
    return searchRecursive(nums, target, nums.begin(), nums.end(), true, true);
  }
  
private:
  int searchRecursive(vector<int> &nums, int target, vector<int>::iterator head,
                      vector<int>::iterator tail, bool leftUnsure, bool rightUnsure) {
    if (head >= tail) 
      return -1;
    
    decltype(head) mid, quarter, iiiQuar;
    mid = head + ((tail - head) >> 1);
    quarter = head + ((mid - head) >> 1);
    iiiQuar = mid + ((tail - mid) >> 1);
    
    if (*mid == target)
      return mid - nums.begin();
    if (*quarter == target)
      return quarter - nums.begin();
    if (*iiiQuar == target)
      return iiiQuar - nums.begin();
    
    // ..2..3..1..
    if (*mid > *iiiQuar) {
      if (target < *quarter && target > *iiiQuar) {
        return max(
          searchRecursive(nums, target, head, quarter, false, false),
          searchRecursive(nums, target, iiiQuar + 1, tail, false, false));
      }
      if (target > *quarter && target < *mid)
        return searchRecursive(nums, target, quarter + 1, mid, false, false);
      else
        return searchRecursive(nums, target, mid + 1, iiiQuar, true, true);
    }
    
    // ..3..1..2..
    if (*quarter > *mid) {
      if (target < *quarter && target > *iiiQuar) {
        return max(
          searchRecursive(nums, target, head, quarter, false, false),
          searchRecursive(nums, target, iiiQuar + 1, tail, false, false));
      }
      if (target > *mid && target < *iiiQuar)
        return searchRecursive(nums, target, mid + 1, iiiQuar, false, false);
      else
        return searchRecursive(nums, target, quarter + 1, mid, true, true);
    }
    
    // ..1..2..3..
    if ((leftUnsure && rightUnsure && (target < *quarter || target > *iiiQuar))
        || (leftUnsure && target > *iiiQuar)
        || (rightUnsure && target < *quarter)) {
      return max(
        searchRecursive(nums, target, head, quarter, leftUnsure, rightUnsure),
        searchRecursive(nums, target, iiiQuar + 1, tail, leftUnsure, rightUnsure));
    }
    
    if (target < *quarter)
      return searchRecursive(nums, target, head, quarter, leftUnsure, false);
    if (target < *mid)
      return searchRecursive(nums, target, quarter + 1, mid, false, false);
    if (target < *iiiQuar)
      return searchRecursive(nums, target, mid + 1, iiiQuar, false, false);
    
    return searchRecursive(nums, target, iiiQuar + 1, tail, false, rightUnsure);
  }
};

int main()
{
  Solution s;
  deque<int> data = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20
  };
  
  for (auto i = data.size(); i != 0; --i) {
    vector<int> nums(data.begin(), data.end());
    
    for (auto d : data)
      cout << s.search(nums, d) << ' ';
    cout << endl;
    
    data.push_back(data.front());
    data.pop_front();
  }
  
  return 0;
}