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
	map<TreeNode*, int> hash;
public:
	int rob(TreeNode* root)
	{
		if (root == nullptr) return 0;
		map<TreeNode*, int>::iterator it;
		if ((it = hash.find(root)) != hash.end()) return it->second;
		
		int ans = 0;

		if (root->left) ans += rob(root->left->left) + rob(root->left->right);
		if (root->right) ans += rob(root->right->left) + rob(root->right->right);

		ans = max(ans + root->val, rob(root->left) + rob(root->right));
		hash[root] = ans;

		return ans;
	}
};