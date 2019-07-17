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
	struct node
	{
		TreeNode *root;
		int times;
		node(TreeNode *r, int t = 0) :root(r), times(t) {}
	};
public:
	vector<int> inorderTraversal(TreeNode* root)
	{
		stack<node> st;
		vector<int> res;
		if (root)
		{
			st.push(node(root));
			while (!st.empty())
			{
				node cur = st.top();
				st.pop();
				if (++cur.times == 2)
				{
					res.push_back(cur.root->val);
					if (cur.root->right) st.push(node(cur.root->right));
				}
				else
				{
					st.push(cur);
					if (cur.root->left) st.push(node(cur.root->left));
				}
			}
		}
		return res;
	}
};