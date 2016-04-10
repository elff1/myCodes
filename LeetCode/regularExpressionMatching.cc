#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  bool isMatch(string s, string p) {
    // haoel has a better solution.
    return isMatchIter(s.begin(), s.end(), p.begin(), p.end());
  }
private:
  bool isMatchIter(string::iterator sBeg, string::iterator sEnd, string::iterator pBeg, string::iterator pEnd) {
    char ch;
    starFoundAndPassed(pBeg, pEnd);
    
    // bool matched = false;
    bool hasStar = false;
    char starCh = '*';
    while (sBeg != sEnd && pBeg != pEnd) {
      ch = *pBeg;
      auto pBegCur = pBeg;
      ++pBeg;
      
      if (!starFoundAndPassed(pBeg, pEnd)) {
        if (ch != *sBeg && ch != '.') {
          if (hasStar) {
            hasStar = false;
            
            if (*sBeg == starCh) {
              for (; sBeg != sEnd && *sBeg == starCh; ++sBeg);
              --pBeg;
              
              continue;
            }
            
            if (starCh == '.') {
              for (auto iter = sBeg; iter != sEnd; ++iter) {
                if (isMatchIter(iter + 1, sEnd, pBegCur, pEnd))
                  return true;
              }
            }
          }
        
          return false;
        }
        
        if (hasStar && !(ch == '.' && starCh == '.')) {
          if (ch == '.' || starCh == '.') {
            for (auto iter = sBeg; iter != sEnd && (*iter == starCh || starCh == '.'); ++iter) {
              if (isMatchIter(iter + 1, sEnd, pBegCur, pEnd))
                return true;
            }
          }
          
          if (ch != starCh)
            hasStar = false;
        }
        
        ++sBeg;
        continue;
      } else {
        if (hasStar) {
          if (starCh == '.')
            continue;
          if (ch == '.') {
            starCh = ch;
            continue; 
          }
          
          if (ch != starCh) {
            for (auto iter = sBeg; iter != sEnd && *iter == starCh; ++iter) {
              if (isMatchIter(iter + 1, sEnd, pBegCur, pEnd))
                return true;
            }
          }
        } else {
          hasStar = true;
        }
        
        starCh = ch;
      }
    }
    
    if (hasStar)
      for (; sBeg != sEnd && (*sBeg == starCh || starCh == '.'); ++sBeg);
    
    if (pBeg != pEnd) {
      if (pBeg + 1 != pEnd && *(pBeg + 1) == '*')
        return isMatchIter(sBeg, sEnd, pBeg + 2, pEnd);
    }
    
    if (sBeg == sEnd && pBeg == pEnd)
      return true;
    
    return false;
  }
  
  bool starFoundAndPassed(string::iterator &beg, string::iterator end) {
    bool found = false;
    while (beg != end && *beg == '*') {
      ++beg;
      found = true;
    }
    
    return found;
  }
};

int main()
{
  Solution s;
  vector<pair<string, string>> data = {
    {"", ""},
    {"a", ""},
    {"", "a"},
    {"abc", "..c*"},
    {"aabcc", "b*a*a*.c*"},
    {"aaabbbcc", "a*ab*.c*"},
    {"abc", "abcde"},
    {"", ".*a*"},
    {"", ".*a"},
    {"abc", ".*"},
    {"abcc", "a.*c"},
    {"bbbba", ".*a*a"},
    {"abb", "a.*b"},
    {"bbba", ".*b"}
  };
  
  for (auto d : data)
    cout << d.first << ", " << d.second << "         " << (s.isMatch(d.first, d.second) ? "true" : "false") << endl;
  
  return 0;
}