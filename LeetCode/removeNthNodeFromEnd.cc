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
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    removeRecursive(head, head, n);
    
    return head;
  }

private:
  int removeRecursive(ListNode *&head, ListNode *p, int &n) {
    if (p == NULL)
      return 1;
    
    auto k = removeRecursive(head, p->next, n);
    if (k < n)
      return k + 1;
    
    if (k == n) {
      if (p == head) {
        head = head->next;
        delete p;
        
        return k;
      } else {
        return k + 1;
      }
    }
    
    if (k == n + 1) {
      auto q = p->next;
      p->next = q->next;
      delete q;
    }
    
    return k + 1;
  }
};

int main()
{
  Solution s;
  vector<vector<int>> data = {
    {2, 4, 3},
    {1, 2, 3, 4, 5}
  };
  
  for (auto d : data)
    for (auto n = d.size(); n != 0; --n)
      PrintOut(s.removeNthFromEnd(BuildList(d), n));
  
  return 0;
}