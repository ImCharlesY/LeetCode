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
    void RecoverTree(vector<int>::iterator postorder, vector<int>::iterator inorder, int size, TreeNode *&root)
	{
		if (size == 0) return;
		root = new TreeNode(*(postorder - 1));
		auto org = inorder;
		for (; *inorder != *(postorder - 1); ++inorder);		//计算分治区间
		int i = inorder - org;
        int j = size - i - 1;
		RecoverTree(postorder - j - 1, org, i, root->left);							//还原左子树
		RecoverTree(postorder - 1, org + i + 1, j, root->right);	//还原右子树
	}
public:
	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder)
	{
		TreeNode* root = nullptr;
		RecoverTree(postorder.end(), inorder.begin(), postorder.size(), root);
		return root;
	}
};