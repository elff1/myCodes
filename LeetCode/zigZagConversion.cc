#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  string convert(string s, int numRows) {
    if (numRows <= 0)
      return string();
    if (numRows == 1)
      return s;
    
    string *rowStrs = new string[numRows];
    int row = 0;
    bool down = true;

    for (auto ch : s) {
      rowStrs[row].append(1, ch);
      if (down) {
        ++row;
        if (row == numRows - 1)
          down = false;
      } else {
        --row;
        if (row == 0)
          down = true;
      }
    }
    
    string ans(rowStrs[0]);
    for (int i = 1; i < numRows; ++i)
      ans.append(rowStrs[i]);
    delete [] rowStrs;
    
    return ans; 
  }
};

int main()
{
  Solution s;
  vector<pair<string, int>> data = {
    {"paypalishiring", 3}
  };
  
  for (auto d : data)
    cout << s.convert(d.first, d.second) << endl;
  
  return 0;
}