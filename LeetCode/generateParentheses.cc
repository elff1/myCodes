#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<string> generateParenthesis(int n) {
    vector<string> ans;
    
    generate(ans, n, n, "");
    
    return ans;
  }
  
  void generate(vector<string> &ans, int left, int right, string s) {
    if (left == 0 && right == 0)
      ans.push_back(s);
    
    if (left > 0)
      generate(ans, left - 1, right, s + '(');
    
    if (right > 0 && right > left)
      generate(ans, left, right - 1, s + ')');
  }
};

int main()
{
  Solution s;
  vector<int> data = {
    1, 2, 3, 4, 5
  };
  
  for (auto d : data) {
    for (auto str : s.generateParenthesis(d))
      cout << str << ' ';
    cout << endl;
  }
  
  return 0;
}