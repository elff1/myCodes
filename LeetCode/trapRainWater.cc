#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int trap(vector<int> &height) {
    int n = height.size();
    if (n < 3)
      return 0;
    
    int leftPeak = 0;
    for (; leftPeak + 1 < n && height[leftPeak + 1] >= height[leftPeak]; ++leftPeak);
    
    int rightPeak = n - 1;
    for (; rightPeak > 0 && height[rightPeak - 1] >= height[rightPeak]; --rightPeak);
    
    int ans = 0;
    int i = leftPeak + 1, j = rightPeak - 1;
    while (leftPeak < rightPeak) {
      for (; i < rightPeak && height[i] <= height[leftPeak]; ++i);
      for (; j > leftPeak && height[j] <= height[rightPeak]; --j);
      if (i >= rightPeak && j <= leftPeak) {
        ans += count(height, leftPeak, rightPeak);
        leftPeak = rightPeak;
      } else if (i >= rightPeak) {
        ans += count(height, j, rightPeak);
        rightPeak = j;
      } else if (j <= leftPeak) {
        ans += count(height, leftPeak, i);
        leftPeak = i;
      } else {
        ans += count(height, leftPeak, i);
        leftPeak = i;
        
        ans += count(height, j, rightPeak);
        rightPeak = j;
      }
    }
    
    return ans;
  }
  
private:
  int count(vector<int> &height, int left, int right) {
    if (left + 1 >= right)
      return 0;
    
    int h = min(height[left], height[right]);
    int ans = 0;
    for (int i = left + 1; i < right; ++i) {
      if (height[i] < h)
        ans += h - height[i];
    }
    
    return ans;
  }
};

int main()
{
  Solution s;
  vector<vector<int>> data = {
    {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}, // 6
    {5, 4, 1, 2}, // 1
    {5, 2, 1, 2, 1, 5}, // 14
    {6,4,2,0,3,2,0,3,1,4,5,3,2,7,5,3,0,1,2,1,3,4,6,8,1,3}, // 83
    {9, 6, 8, 8, 5, 6, 3} // 3
  };
  
  for (auto d : data)
    cout << s.trap(d) << endl;
  
  return 0;
}