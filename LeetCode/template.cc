#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  
};

int main()
{
  Solution s;
  vector<int> data = {
    
  };
  
  vector<int> results = {
    
  };
  
  int i = 0;
  for (auto d : data) {
    auto result = d;
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