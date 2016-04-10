#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  const int MaxInt = (unsigned)~0 >> 1;
  const int MinInt = -MaxInt - 1;
  
  int reverse(int x) {
    int y = 0;
    int sign = (x > 0) ? 1 : -1;
    x *= sign;
    
    int digit = 0;
    while (x > 0) {
      digit = x % 10;
      x /= 10;
      
      if ((sign == 1 && (y < MaxInt / 10 || (y == MaxInt / 10 && digit <= MaxInt % 10)))
        || (sign == -1 && (y > MinInt / 10 || (y == MinInt / 10 && digit <= (10 - MinInt % 10) % 10))))
      {
        y = y * 10 + sign * digit;
      }
      else
        return 0;
    }
    
    return y;
  }
};

int main()
{
  Solution s;
  vector<int> data = {
    1234567890,
    2123456789,
    -1234567890
  };
  
  for (auto d : data)
    cout << s.reverse(d) << endl;
  
  return 0;
}