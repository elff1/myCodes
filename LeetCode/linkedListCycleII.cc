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
  ListNode *detectCycle(ListNode *head) {
    auto fast = head, slow = head;
    
    while (fast) {
      if (fast->next) {
        fast = fast->next->next;
        slow = slow->next;
        
        if (fast == slow)
          break;
      }
      else
        break;
    }
    
    if (!fast || !fast->next)
      return NULL;
    
    fast = head;
    while (fast != slow) {
      fast = fast->next;
      slow = slow->next;
    }
    
    return fast;
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