#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
  int divide(int dividend, int divisor) {
    if (divisor == 0)
      return INT_MAX;
    
    if (dividend == INT_MIN && divisor == -1)
      return INT_MAX;
    
    auto sd = !(dividend < 0);
    auto si = !(divisor < 0);
    auto dd = sd ? (unsigned)dividend : (unsigned)-dividend;
    auto di = si ? (unsigned)divisor : (unsigned)-divisor;
    auto bd = getBits(dd);
    auto bi = getBits(di);
    
    unsigned ans = 0;
    for (int bit = bd - bi; bit >= 0; --bit) {
      if (dd >= di << bit) {
        ans += 1 << bit;
        dd -= di << bit;
      }
    }
    
    return (sd ^ si) ? -ans : ans;
  }
  
private:
  unsigned getBits(unsigned n) {
    auto bit = ((unsigned)-1 >> 1) + 1;
    for (; bit != 0; bit >>= 1)
      if (n & bit) break;
    
    unsigned bits = 0;
    for (; bit != 0; bit >>= 1)
      ++bits;
    
    return bits;
  }
};

int main()
{
  Solution s;
  vector<pair<int, int>> data = {
    {0, 0},
    {0, -1},
    {1, -1},
    {INT_MAX, 1},
    {INT_MAX, -1},
    {INT_MIN, 1},
    {INT_MIN, -1},
    {INT_MIN, INT_MAX},
    {INT_MIN, INT_MIN},
    {INT_MAX, INT_MIN},
    {123, 10},
    {12, 13},
    {27, -3}
  };
  
  for (auto d : data)
    cout << s.divide(d.first, d.second) << endl;
  
  s = s;
  
  return 0;
}