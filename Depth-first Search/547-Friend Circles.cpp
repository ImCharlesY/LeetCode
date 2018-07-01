class Solution
{
public:
	int findCircleNum(vector<vector<int>>& M) 
	{
		int n = M.size();
		int ans = 0;
		stack<int> st;
		vector<int> visited(n, 0);
		for (int i = 0; i < n; ++i)
		{
			if (visited[i]) continue;
			++ans;
			st.push(i);
			visited[i] = 1;
			while (!st.empty())
			{
				auto cur = st.top(); st.pop();
				for (int j = 0; j < n; ++j)
					if (M[cur][j] && !visited[j])
					{
						st.push(j);
						visited[j] = 1;
					}	
			}
		}
		return ans;
	}
};