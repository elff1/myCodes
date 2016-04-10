#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  static const int MaxInt = (unsigned)~0 >> 1;
  static const int MinInt = -MaxInt - 1;
  
  int myAtoi(string str) {
    unsigned ans = 0;
    
    auto iter = str.begin();
    for (; iter != str.end() && isspace(*iter); ++iter);
    
    if (iter == str.end())
      return ans;
    
    int sign = 1;
    if (*iter == '+' || *iter == '-') {
      if (*iter == '-')
        sign = -1;
      ++iter;
    }
    
    unsigned digit;
    for (; iter != str.end() && isdigit(*iter); ++iter) {
      digit = *iter - '0';
      
      if (sign == 1 && (ans > (unsigned)MaxInt / 10 || (ans == (unsigned)MaxInt / 10 && digit > MaxInt % 10))) {
        return MaxInt;
      } else if (sign == -1 && (ans > (unsigned)MinInt / 10 || (ans == (unsigned)MinInt / 10 && digit > (unsigned)MinInt % 10))) {
        return MinInt;
      }
      ans = ans * 10 + digit;
    }
    
    return sign > 0 ? ans : -ans;
  }
};

int main()
{
  Solution s;
  vector<string> data = {
    "1234567890",
    "2345678901",
    "-1234567890",
    "-2345678901",
    "   -34e44",
    "+ 34",
    "+2134 45",
    "",
    "  "
  };
  
  for (auto d : data)
    cout << s.myAtoi(d) << endl;
  
  return 0;
}