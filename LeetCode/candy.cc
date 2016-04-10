#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int candy(vector<int> &ratings) {
    int n = ratings.size();
    int preIndex = -1, preCandy = 0;
    int ans = 0;
    int curCandy, j;
    
    for (int i = 0; i < n; ++i) {
      if (i + 1 < n && ratings[i] > ratings[i + 1])
        continue;
      
      for (curCandy = 0, j = i; j != preIndex; --j) {
        if (preIndex + 1 == j && ratings[preIndex] < ratings[j] && preCandy > curCandy)
          curCandy = preCandy;
        ans += ++curCandy;
      }
      
      if (i + 1 < n && ratings[i] < ratings[i + 1]) {
        for (curCandy = 1, ++i; i + 1 < n && ratings[i] < ratings[i + 1]; ++i)
          ans += ++curCandy;
        preCandy = curCandy;
        preIndex = --i;
      } else {
        preCandy = 1;
        preIndex = i;
      }
    }
    
    return ans;
  }
};

int main()
{
  Solution s;
  vector<vector<int>> data = {
    {},
    {1},
    {2, 1, 1, 3, 4},
    {1, 2},
    {1, 1, 1, 1},
    {1, 3, 4, 3, 2, 1},
    {1, 3, 4, 4, 4, 3, 2, 1}
  };
  
  for (auto d : data)
    cout << s.candy(d) << endl;
  
  return 0;
}