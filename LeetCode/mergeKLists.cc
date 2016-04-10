#include <iostream>
#include <vector>
#include <algorithm>

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
  ListNode *mergeKLists(vector<ListNode *> &lists) {
    for (auto iter = lists.begin(); iter != lists.end();) {
      if (*iter == NULL)
        iter = lists.erase(iter);
      else
        ++iter;
    }
    
    if (lists.size() == 0)
      return NULL;
      
    make_heap(lists.begin(), lists.end(), minHeapComp);
    
    ListNode *head = NULL;
    ListNode **pTail = &head;
    while (lists.size() != 1) {
      pop_heap(lists.begin(), lists.end(), minHeapComp);
      *pTail = lists.back();
      pTail = &(*pTail)->next;
      
      if (*pTail == NULL)
        lists.pop_back();
      else {
        lists.back() = *pTail;
        push_heap(lists.begin(), lists.end(), minHeapComp);
      }
    }
    *pTail = lists.front();    
    lists.erase(lists.begin());
    
    return head;
  }
  
private:
  static bool minHeapComp(const ListNode *p, const ListNode *q) {
    return p->val > q->val;
  }
};

int main()
{
  Solution s;
  vector<vector<vector<int>>> data = {
    {{}},
    {{1, 2, 5}, {3, 6}, {}},
    {{}, {4, 6}, {2, 5}, {10}},
    {{}, {}, {}}
  };
  
  for (auto d : data) {
    vector<ListNode *> lists;
    for (auto l : d)
      lists.push_back(BuildList(l));
    
    PrintOut(s.mergeKLists(lists));
  }
  
  return 0;
}