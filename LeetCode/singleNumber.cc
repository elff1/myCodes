#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int singleNumber(vector<int> &nums) {
    int ans = 0;
    
    for (auto num : nums) {
      ans ^= num;
    }
    
    return ans;
  }
};

int main()
{
  Solution s;
  vector<int> data = {
    -432, 24121, 32, 0, 0, -54324, -432, 32, 24121
  };
  
  cout << s.singleNumber(data) << endl;
  
  return 0;
}