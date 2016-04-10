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
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    vector<int> ans;
    int carry = 0;
    int digit;
    
    while (l1 != NULL || l2 != NULL) {
      if (l1 == NULL) {
        digit = l2->val + carry;
        l2 = l2->next;
      }
      else if (l2 == NULL) {
        digit = l1->val + carry;
        l1 = l1->next;
      }
      else {
        digit = l1->val + l2->val + carry;
        l1 = l1->next;
        l2 = l2->next;
      }
      carry = digit / 10;
      ans.push_back(digit % 10);
    }
    if (carry > 0)
      ans.push_back(carry);
    
    return BuildList(ans);
  }
};

int main()
{
  Solution s;
  vector<int> v1{2, 4, 3}, v2{5, 6, 6};
  
  auto l1 = BuildList(v1);
  auto l2 = BuildList(v2);
  
  PrintOut(s.addTwoNumbers(l1, l2));
  return 0;
}