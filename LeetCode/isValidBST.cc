#include <iostream>
#include <vector>

using namespace std;

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
 
class Solution {
public:
  bool isValidBST(TreeNode *root) {
    bool hasPreNum = false;
    int preNum;
    return verifyBST(root, hasPreNum, preNum);
  }
  
private:
  bool verifyBST(TreeNode *node, bool &hasPreNum, int &preNum) {
    if (!node)
      return true;
    
    if (!verifyBST(node->left, hasPreNum, preNum))
      return false;
    
    if (!hasPreNum) {
      hasPreNum = true;
      preNum = node->val;
    } else {
      if (node->val <= preNum)
        return false;
      preNum = node->val;
    }
    
    if (!verifyBST(node->right, hasPreNum, preNum))
      return false;
    
    return true;
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