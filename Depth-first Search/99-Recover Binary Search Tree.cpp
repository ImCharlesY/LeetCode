/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution
{
	TreeNode* firstNode = nullptr;
	TreeNode* secondNode = nullptr;
	TreeNode* preNode;
	void InOrderTraversal(TreeNode* root)
	{
		if (!root) return;
		InOrderTraversal(root->left);
		if (!firstNode && preNode->val >= root->val) firstNode = preNode;
		if (firstNode && preNode->val >= root->val) secondNode = root;
		preNode = root;
		InOrderTraversal(root->right);
	}
public:
	void recoverTree(TreeNode* root) 
	{
		preNode = new TreeNode(INT_MIN);
		InOrderTraversal(root);
		swap(firstNode->val, secondNode->val);
	}
};