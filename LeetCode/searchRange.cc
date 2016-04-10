#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> searchRange(vector<int> &nums, int target) {
    return vector<int>{searchBorder(nums, target, true), searchBorder(nums, target, false)};
  }
  
private:
  int searchBorder(vector<int> &nums, int target, bool leftBorder) {
    auto head = nums.begin();
    auto tail = nums.end();
    decltype(head) mid;
    
    while (head < tail) {
      mid = head + ((tail - head) >> 1);
      
      if (target == *mid) {
        if (leftBorder) {
          if (mid > nums.begin() && target == *(mid - 1))
            tail = mid;
          else
            return mid - nums.begin();
        } else {
          if (mid + 1 < nums.end() && target == *(mid + 1))
            head = mid + 1;
          else
            return mid - nums.begin();
        }
      }
      else if (target < *mid)
        tail = mid;
      else
        head = mid + 1;
    }
    
    return -1;
  }
};

int main()
{
  Solution s;
  vector<int> data = {
    5, 7, 7, 8, 8, 10
  };
  
  auto ans = s.searchRange(data, 8);
  cout << ans[0] << ' ' << ans[1] << endl;
  
  return 0;
}