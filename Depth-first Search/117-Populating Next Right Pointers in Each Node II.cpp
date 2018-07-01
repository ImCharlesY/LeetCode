/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution 
{
public:
    void connect(TreeLinkNode *root) 
    {
        if (root == nullptr) return;
        TreeLinkNode* pre = root;
        TreeLinkNode* cur = nullptr;
        while(pre->left || pre->right)
        {
            cur = pre;
            while(cur)
            {
                if (cur->left && cur->right)
                {
                    cur->left->next = cur->right;
                    auto tmp = cur;
                    while (tmp->next && tmp->next->left == nullptr && tmp->next->right == nullptr) tmp = tmp->next;
                    if (tmp->next) cur->right->next = (tmp->next->left) ? tmp->next->left : tmp->next->right;
                }
                else if (cur->left)
                {
                    auto tmp = cur;
                    while (tmp->next && tmp->next->left == nullptr && tmp->next->right == nullptr) tmp = tmp->next;
                    if (tmp->next) cur->left->next = (tmp->next->left) ? tmp->next->left : tmp->next->right;
                }
                else if (cur->right)
                {          
                    auto tmp = cur;
                    while (tmp->next && tmp->next->left == nullptr && tmp->next->right == nullptr) tmp = tmp->next;
                    if (tmp->next) cur->right->next = (tmp->next->left) ? tmp->next->left : tmp->next->right;
                } 
                cur = cur->next;
            }
            pre = (pre->left) ? pre->left : pre->right;
            while (pre->left == nullptr && pre->right == nullptr && pre->next) pre = pre->next;
        }
    }
};