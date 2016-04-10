#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  string intToRoman(int num) {
    if (num <= 0)
      return "";
    
    string romanNum;
    
    int digit;
    for (int bit = 0; num > 0; ++bit, num /= 10) {
      string romanBit;
      digit = num % 10;
      if (digit == 9) {
        romanBit = RomanSymbol[bit].first + RomanSymbol[bit + 1].first;
      } else if (digit > 4) {
        romanBit = RomanSymbol[bit].second;
        for (auto i = digit - 5; i != 0; --i)
          romanBit += RomanSymbol[bit].first;
      } else if (digit == 4) {
        romanBit = RomanSymbol[bit].first + RomanSymbol[bit].second;
      } else {
        for (auto i = digit; i != 0; --i)
          romanBit += RomanSymbol[bit].first;
      }
      
      romanNum = romanBit + romanNum;
    }
    
    return romanNum;
  }
  
private:
  static const vector<pair<string, string>> RomanSymbol;
};

const vector<pair<string, string>> Solution::RomanSymbol = {
  {"I", "V"},
  {"X", "L"},
  {"C", "D"},
  {"M", ""}
};

int main()
{
  Solution s;
  vector<int> data = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1954, 1990, 2014
  };
  
  for (auto d : data)
    cout << s.intToRoman(d) << endl;
  
  return 0;
}