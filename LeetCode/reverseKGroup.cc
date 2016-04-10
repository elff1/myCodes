#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

void PrintOut(ListNode *head)
{
  while (head != NULL)
  {
    cout << head->val << ' ';
    head = head->next;
  }
  cout << endl;
}

ListNode *BuildList(const vector<int> digits)
{
  ListNode *head = NULL, *p, *q;
  for (auto digit : digits)
  {
    q = new ListNode(digit);
    if (head == NULL)
    {
      p = q;
      head = p;
    }
    else
    {
      p->next = q;
      p = q;
    }
  }
  return head;
}

class Solution {
public:
  ListNode *reverseKGroup(ListNode *head, int k) {
    if (k <= 1 || !head)
      return head;
    
    ListNode dummyHead(0);
    dummyHead.next = head;
    
    auto preNode = &dummyHead;
    auto curNode = head;
    auto nextNode = head->next;
    
    int count = 1;
    while (true) {
      if (count < k) {
        if (nextNode) {
          curNode->next = nextNode->next;
          nextNode->next = preNode->next;
          preNode->next = nextNode;
          
          nextNode = curNode->next;
          
          ++count;
        } else {
          curNode = preNode->next;
          nextNode = curNode->next;
          
          k = count;
          count = 1;
        }
      } else if (nextNode) {
        preNode = curNode;
        curNode = nextNode;
        nextNode = curNode->next;
        
        count = 1;
      } else
        break;
    }
    
    return dummyHead.next;
  }
};

int main()
{
  Solution s;
  vector<vector<int>> data = {
    {},
    {1},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}
  };
  
  for (auto d : data) {
    auto h = BuildList(d);
    for (auto k = d.size() + 1; k != 0; --k)
      PrintOut(h = s.reverseKGroup(h, k));
    cout << endl;
  }
  
  return 0;
}