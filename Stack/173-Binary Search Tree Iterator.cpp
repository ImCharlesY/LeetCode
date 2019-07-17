/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator 
{
	struct node
	{
		TreeNode *root;
		int times;
		node(TreeNode *r, int t = 0) :root(r), times(t) {}
	};
	vector<int> res;
	int index;
public:
	BSTIterator(TreeNode *root) 
	{
		stack<node> st;
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
		index = 0;
	}

	/** @return whether we have a next smallest number */
	bool hasNext() 
	{
		return index < res.size();
	}

	/** @return the next smallest number */
	int next() 
	{
		return res[index++];
	}
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */