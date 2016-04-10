#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};
 
class Solution {
public:
  RandomListNode *copyRandomList(RandomListNode *head) {
    unordered_map<RandomListNode *, RandomListNode *> map;
    RandomListNode *newHead = NULL;
    RandomListNode *p = head, *q, *r;
    
    while (p) {
      r = new RandomListNode(p->label);
      if (!newHead) {
        newHead = r;
        q = r;
      } else {
        q->next = r;
        q = r;
      }
      
      map[p] = r;
      p = p->next;
    }
    
    for (p = head; p; p = p->next) {
      if (p->random) {
        map[p]->random = map[p->random];
      }
    }
    
    return newHead;
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