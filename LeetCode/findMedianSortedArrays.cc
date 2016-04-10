#include <iostream>
#include <vector>

using namespace std;

// O(log(m + n))
class Solution {
public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    auto length = nums1.size() + nums2.size();
    
    return (length % 2) ? findKthSortedArrays(nums1, nums2, length / 2)
      : (findKthSortedArrays(nums1, nums2, length / 2 - 1) + findKthSortedArrays(nums1, nums2, length / 2)) / 2; 
  }
  
  double findKthSortedArrays(vector<int> &nums1, vector<int> &nums2, unsigned k) {
    auto iter1 = nums1.begin();
    auto iter2 = nums2.begin();
    auto size1 = nums1.size();
    auto size2 = nums2.size();
    auto length = size1 + size2;
    
    if (length == 0 || k >= length)
      return 0;
    
    unsigned k1, k2;
    for (;;) {
      if (size1 > size2) {
        swap(iter1, iter2);
        swap(size1, size2);
      }
      
      if (size1 == 0)
        return iter2[k];
      
      if (length == k + 1)
        return iter1[size1-1] > iter2[size2-1] ? iter1[size1-1] : iter2[size2-1];
      
      if (k < size1 / 2) {
        k1 = k /2;
        k2 = k - k1;
      } else if (k > size2) {
        k2 = (size2 - 1) - (length - k) / 2;
        k1 = k - k2;
      } else {
        k1 = size1 / 2;
        k2 = k - k1;
      }
      
      if (iter1[k1] < iter2[k2]) {
        iter1 += k1;
        size1 -= k1;
        size2 = k2;
        k = k2;
      } else {
        iter2 += k2;
        size2 -= k2;
        size1 = k1;
        k = k1;
      }
      
      length = size1 + size2;
    }
  }
};

// O(m + n)
class Solution1 {
public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    auto iter1 = nums1.begin();
    auto iter2 = nums2.begin();
    auto length = nums1.size() + nums2.size();
    auto medIndex = length >> 1;
    int preMedian = 0;
    
    for (auto i = medIndex; i != 0; --i) {
      preMedian = getSmallerNumAndMoveIter(iter1, iter2, nums1.end(), nums2.end());
    }
    
    double median = getSmallerNumAndMoveIter(iter1, iter2, nums1.end(), nums2.end());
    return length % 2 ? median : (preMedian + median) / 2;
  }
  
private:
  int getSmallerNumAndMoveIter(vector<int>::iterator &iter1, vector<int>::iterator &iter2,
                                vector<int>::iterator end1, vector<int>::iterator end2)
  {
    vector<int>::iterator *iterPtr;
    
    if (iter1 == end1 && iter2 == end2)
      iterPtr = nullptr;
    else if (iter1 == end1)
      iterPtr = &iter2;
    else if (iter2 == end2)
      iterPtr = &iter1;
    else if (*iter1 < *iter2)
      iterPtr = &iter1;
    else
      iterPtr = &iter2;
    
    if (iterPtr == nullptr)
      return 0;
    
    return *(*iterPtr)++;
  }
};

int main()
{
  Solution s;
  vector<pair<vector<int>, vector<int>>> data = {
    {{}, {}},
    {{}, {1}},
    {{}, {1, 2, 3, 4}},
    {{1}, {2}},
    {{1, 3}, {2}},
    {{1, 3}, {2, 4, 5}},
    {{2, 4, 5}, {1, 3}},
    {{2, 4, 6}, {1, 3, 5}},
    {{1, 3, 5}, {2, 4, 6, 8}}
  };
  
  for (auto d : data) {
    cout << s.findMedianSortedArrays(d.first, d.second) << endl;
    for (int i = d.first.size() + d.second.size() - 1; i >= 0; --i)
      cout << s.findKthSortedArrays(d.first, d.second, i) << ' ';
    cout << endl;
  }
  
  return 0;
}