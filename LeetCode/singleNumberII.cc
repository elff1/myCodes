#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int singleNumber(vector<int> &nums) {
    int oneTime = 0, twoTimes = 0, threeTimes = 0;
    
    for (auto num : nums) {
      twoTimes |= oneTime & num;
      oneTime ^= num;
      threeTimes = oneTime & twoTimes;
      oneTime &= ~threeTimes;
      twoTimes &= ~threeTimes;
    }
    
    return oneTime;
  }
};

int main()
{
  Solution s;
  vector<int> data = {
    -432, 24121, 32, 0, 0, -54324, -432, 32, 24121, 32, 24121, -432
  };
  
  cout << s.singleNumber(data) << endl;
  
  return 0;
}