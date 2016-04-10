#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<string> letterCombinations(string digits) {
    vector<int> nums, bits(digits.size(), 0);
    
    for (auto digit : digits)
      nums.push_back(digit - '0');
    
    letters.erase(letters.begin(), letters.end());
    
    walkThroughDigits(0, nums, bits);
    
    return letters;
  }
  
private:
  vector<string> letters;
  static const vector<string> dictionary;
  
  void walkThroughDigits(unsigned k, const vector<int> &nums, vector<int> &bits) {
    auto length = nums.size();
    
    if (length == 0)
      return;
    
    if (k == length) {
      string letter;
      for (unsigned i = 0; i != length; ++i)
        letter.push_back(dictionary[nums[i]][bits[i]]);
      
      letters.push_back(letter);
      return;
    }
    
    const string &digitLetter = dictionary[nums[k]];
    for (unsigned i = 0; i != digitLetter.size(); ++i) {
      bits[k] = i;
      walkThroughDigits(k + 1, nums, bits);
    }
  }
};

const vector<string> Solution::dictionary = {
  " ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};

int main()
{
  Solution s;
  vector<string> data = {
    "23",
    ""
  };
  
  for (auto d : data) {
    auto ans = s.letterCombinations(d);
    for (auto letter : ans)
      cout << letter << ' ';
    cout << endl;
  }
  
  return 0;
}