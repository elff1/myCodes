#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  void reorderList(ListNode *head) {
    auto midPtr = getMidPtr(head);
    if (!midPtr || !midPtr->next)
      return;
    
    auto secHead = reverseList(midPtr->next);
    midPtr->next = NULL;
    
    mergerLists(head, secHead);
  }
  
private:
  ListNode *getMidPtr(ListNode *head) {
    if (!head)
      return head;
    
    ListNode *fast = head, *slow = head;
    while (fast->next && fast->next->next) {
      slow = slow->next;
      fast = fast->next->next;
    }
    
    return slow;
  }
  
  ListNode *reverseList(ListNode *head) {
    ListNode dummy(0);
    
    ListNode *tmp;
    while (head) {
      tmp = head->next;
      
      head->next = dummy.next;
      dummy.next = head;
      
      head = tmp;
    }
    
    return dummy.next;
  }
  
  void mergerLists(ListNode *firHead, ListNode *secHead) {
    auto p = firHead;
    ListNode *tmp;
    while (secHead) {
      tmp = p->next;
      
      p->next = secHead;
      p = tmp;
      swap(tmp, secHead->next);
      
      secHead = tmp;
    }
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