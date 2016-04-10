#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int compareVersion(string version1, string version2) {
    auto v1 = split(version1);
    auto v2 = split(version2);
    auto i1 = v1.begin();
    auto i2 = v2.begin();
    while (i1 != v1.end() && i2 != v2.end()) {
      if (*i1 < *i2)
        return -1;
      if (*i1 > *i2)
        return 1;
      ++i1;
      ++i2;
    }
    if (i1 != v1.end()) {
      while (*i1 == 0) {
        ++i1;
        if (i1 == v1.end())
          return 0;
      }
      return 1;
    }
    if (i2 != v2.end()) {
      while (*i2 == 0) {
        ++i2;
        if (i2 == v2.end())
          return 0;
      }
      return -1;
    }
    return 0;
  }
  
private:
  vector<int> split(string version) {
    vector<int> ans;
    if (version.empty())
      return ans;
    
    string::size_type leftBorder = 0, dotIndex, len;
    do {
      dotIndex = version.find('.', leftBorder);
      if (dotIndex == string::npos)
        len = dotIndex;
      else
        len = dotIndex - leftBorder;
      ans.push_back(stoi(version.substr(leftBorder, len)));
      leftBorder = dotIndex + 1;
    } while (dotIndex != string::npos);
    
    return ans;
  }
};

int main()
{
  Solution s;
  vector<pair<string, string>> data = {
    {"0", "0.0"},
    {"0.0", "1"},
    {"1.0", ""},
    {"0.1", "0.1"},
    {"0.1.0.3", "0.1.0.2"}
  };
  
  vector<int> results = {
    0,
    -1,
    1,
    0,
    1
  };
  
  int i = 0;
  for (auto d : data) {
    int result = s.compareVersion(d.first, d.second);
    if (result != results[i]) {
      cout << "Test case " << i << ": \nE\"";
      cout << results[i] << "\"\nO\"";
      cout << result << "\"" << endl;
    } else {
      cout << "Test case " << i << " passed." << endl;
    }
    ++i;
  }
  s = s;
  
  return 0;
}