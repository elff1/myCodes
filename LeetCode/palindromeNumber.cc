#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  bool isPalindrome(int x) {
    if (x < 0)
      return false;
    
    auto n = (unsigned)x; // x < 0 ? (unsigned)~0 - (unsigned)x + 1 : x;

    int bits = 0;
    for (; x != 0; ++bits, x /= 10);
    
    unsigned backHalf = 0;
    for (int i = 1; i < bits; i += 2) {
      backHalf = backHalf * 10 + n % 10;
      n /= 10;
    }
    
    if ((bits & 1) == 1)
      n /= 10;
    
    return n == backHalf;
  }
};

int main()
{
  Solution s;
  vector<int> data = {
    0,
    -1,
    121,
    1221,
    123,
    1223,
    -123454321
  };
  
  for (auto d : data)
    cout << s.isPalindrome(d) << endl;
  
  return 0;
}