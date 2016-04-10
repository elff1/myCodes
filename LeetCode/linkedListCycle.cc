#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int label;
    ListNode *next;
    ListNode(int x) : label(x), next(NULL) {}
};

class Solution {
public:
  bool hasCycle(ListNode *head) {
    auto fast = head, slow = head;
    
    while (fast) {
      if (fast->next) {
        fast = fast->next->next;
        slow = slow->next;
        
        if (fast == slow)
          return true;
      }
      else
        break;
    }
    
    return false;
  }
};

int main()
{
  Solution s;
  vector<int> data = {
    
  };
  
  for (auto d : data)
    cout << d << endl;
  
  s = s;
  
  return 0;
}