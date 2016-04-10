#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
  vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    eliminateDuplicated(candidates);
    
    vector<vector<vector<int>>> ans(target + 1);
    ans[0].push_back(vector<int>());
    for (auto c : candidates) {
      for (auto t = c; t <= target; ++t) {
        if (!ans[t - c].empty()) {
          for (auto a : ans[t - c]) {
            a.push_back(c);
            ans[t].push_back(a);
          }
        }
      }
    }
    
    return ans[target];
  }
  
private:
  void eliminateDuplicated(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    auto endUnique = unique(nums.begin(), nums.end());
    nums.erase(endUnique, nums.end());
  }
};

int main()
{
  Solution s;
  vector<int> data = {
    // 2, 2, 2, 3, 4
    2, 3, 6, 7
  };
  
  auto ans = s.combinationSum(data, 7);
  
  for (auto &a : ans) {
    for (auto aa : a)
      cout << aa << ' ';
    cout << endl;
  }
  
  return 0;
}