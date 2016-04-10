#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <climits>

using namespace std;
  
class Solution {
public:
  string largestNumber(vector<int> &nums) {
    vector<string> strs;
    for (auto num : nums)
      strs.push_back(to_string(num));
    
    sort(strs.begin(), strs.end(), comp);
    
    if (strs.empty() || strs.front() == "0")
      return "0";
    
    string ans;
    for (auto str : strs)
      ans.append(str);
    
    return ans;
  }

private:
  static bool comp(const string &a, const string &b) {
    if (a.empty() || b.empty())
      return false;
    
    auto aIter = a.begin();
    auto bIter = b.begin();
    while (aIter != a.end() || bIter != b.end()) {
      if (aIter == a.end())
        aIter = a.begin();
      if (bIter == b.end())
        bIter = b.begin();
      
      if (*aIter > *bIter)
        return true;
      if (*aIter < *bIter)
        return false;
      
      ++aIter;
      ++bIter;
    }
    
    return false;
  }
};

int main()
{
  Solution s;
  vector<vector<int>> data = {
    {3, 30, 34, 5, 9},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
    {},
    {0, 0},
    {824,938,1399,5607,6973,5703,9609,4398,8247},
    {121, 12},
    {0,9,8,7,6,5,4,3,2,1}
  };
  
  vector<string> results = {
    "9534330",
    "9876543210",
    "0",
    "0",
    "9609938824824769735703560743981399",
    "12121",
    "9876543210"
  };
  
  int i = 0;
  for (auto d : data) {
    auto result = s.largestNumber(d);
    if (result != results[i]) {
      cout << "Test case " << i << ": \nE\"";
      cout << results[i] << "\"\nO\"";
      cout << result << "\"" << endl;
    }
    ++i;
  }
  
  return 0;
}