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
		int level;
		node(TreeNode *r, int l = 0) :root(r), level(l) {}
	};
public:
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) 	
	{
		vector<deque<int>> tmpres;
		vector<vector<int>> res;
		queue<node> q;
		if (root)
		{
			q.push(node(root, 0));
			while (!q.empty())
			{
				node curNode = q.front();
				q.pop();
				if (tmpres.size()<=curNode.level) tmpres.push_back(deque<int>({ curNode.root->val }));
				else
				{
					if (curNode.level % 2 == 0) tmpres[curNode.level].push_back(curNode.root->val);
					else tmpres[curNode.level].push_front(curNode.root->val);
				}
				if (curNode.root->left) q.push(node(curNode.root->left, curNode.level + 1));
				if (curNode.root->right) q.push(node(curNode.root->right, curNode.level + 1));
			}
		}
		for (auto &item : tmpres)
		{
			vector<int> tmp;
			for (auto &inItem : item) tmp.push_back(inItem);
			res.push_back(tmp);
		}
		return res;
	}
};