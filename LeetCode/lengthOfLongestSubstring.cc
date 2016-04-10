#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void PrintOut(unordered_map<char, int> map) {
  for (auto m : map) {
    cout << "{" << m.first << ", " << m.second << "} ";
  }
  cout << endl;
}

class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    int maxLen = 0, curLen = 0;
    unordered_map<char, int> charMap;
    
    for (auto chatIter = s.begin(); chatIter != s.end(); ++chatIter) {
      auto mapIter = charMap.find(*chatIter);
      int index = chatIter - s.begin();
      
      if (mapIter == charMap.end()) {
        ++curLen;
        maxLen = max(maxLen, curLen);
      } else {
        for (int i = index - curLen; i < mapIter->second; ++i) {
          charMap.erase(s[i]);
          --curLen;
        }
      }
      charMap[*chatIter] = index;
      
      // PrintOut(charMap);
      // cout << curLen << endl;
    }
    
    return maxLen;
  }
};

int main()
{
  Solution s;
  vector<string> testStrings = {
    "dvdf",
    "aaaaaaaa",
    "abccabcd",
    "abcdcbad"
  };
  
  for (auto str : testStrings)
    cout << s.lengthOfLongestSubstring(str) << endl;
  
  return 0;
}