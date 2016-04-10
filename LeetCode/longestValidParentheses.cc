#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
  int longestValidParentheses(string s) {
    unsigned longestLength = 0;
    unsigned curLength = 0;
    unsigned preLength = 0;
    unsigned rpNeeded = 0;
    unsigned smallestNeeded = s.size();
    
    for (auto ch : s) {
      if (ch == ')') {
        if (rpNeeded > 0) {
          ++curLength;
          --rpNeeded;
          
          smallestNeeded = min(smallestNeeded, rpNeeded); 
          if (rpNeeded == 0) {
            preLength += curLength;
            curLength = 0;
            smallestNeeded = s.size();
          }
        } else {
          longestLength = max(longestLength, preLength);
          curLength = 0;
          preLength = 0;
        }
      } else {
        ++curLength;
        ++rpNeeded;
      }
    }
    
    if (smallestNeeded == s.size())
      return max(longestLength, preLength);
    
    return max({longestLength, preLength, (unsigned)longestValidParentheses(s.substr(s.size() - (curLength - smallestNeeded)))});
  }
};

int main()
{
  Solution s;
  vector<string> data = {
    "(()",
    ")()",
    "())",
    "()(()()))()))(())((())(())",
    ")()))()))(())",
    ")()))(())((()",
    "(()(((())"
  };
  
  for (auto d : data)
    cout << s.longestValidParentheses(d) << endl;
  
  return 0;
}