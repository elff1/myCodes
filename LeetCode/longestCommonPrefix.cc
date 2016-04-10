#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  string longestCommonPrefix(vector<string> &strs) {
    if (strs.empty())
      return "";
    
    int index = 0;
    char ch;
    bool checkNextChar = true;
    for (;; ++index) {
      ch = 0;
      for (auto s : strs) {
        if (s.begin() + index == s.end()) {
          checkNextChar = false;
          break;
        }
        
        if (ch != 0 && ch != s[index]) {
          checkNextChar = false;
          break;
        }
          
        ch = s[index];
      }
      
      if (!checkNextChar)
        break;
    }
    
    return strs[0].substr(0, index);
  }
};

int main()
{
  Solution s;
  vector<vector<string>> data = {
    {"a", "a", "a", "a", ""},
    {"abc", "abcd", "abcde", "abce", "abcf"},
    {"", "", "", "", ""},
    {"abc", "abe", "af", "az", "azz"}
  };
  
  for (auto d : data)
    cout << s.longestCommonPrefix(d) << endl;
  
  return 0;
}