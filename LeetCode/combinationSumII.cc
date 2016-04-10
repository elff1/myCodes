#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Solution {
public:
  vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
    sort(candidates.begin(), candidates.end());
    
    vector<vector<vector<int>>> ans(target + 1);
    ans[0].push_back(vector<int>());
    int c, count;
    
    for (auto iter = candidates.begin(); iter != candidates.end(); ) {
      c = *iter;
      for (count = 1; ++iter != candidates.end() && *iter == c; ++count);
      
      for (int t = target; t >= c; --t) {
        auto tt = t - c;
        for (int i = 1; tt >= 0 && i <= count; tt -= c, ++i) {
          for (auto a : ans[tt]) {
            a.insert(a.end(), i, c);
            ans[t].push_back(a);
          }
        }
      }
    }
    
    return ans[target];
  }
};

int main()
{
  Solution s;
  vector<int> data = {
    4,4,2,1,4,2,2,1,3
    // 1, 1, 2, 2, 2, 2
  };
  
  auto ans = s.combinationSum2(data, 6);
  
  for (auto &a : ans) {
    for (auto aa : a)
      cout << aa << ' ';
    cout << endl;
  }
  
  return 0;
}