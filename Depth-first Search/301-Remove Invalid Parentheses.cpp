class Solution
{
	bool isValid(string s)
	{
		stack<char> st;
		for (auto c : s)
		{
			if (c == '(') st.push(c);
			else if (c == ')')
			{
				if (st.empty() || st.top() != '(') return  0;
				st.pop();
			}
		}
		return st.empty();
	}
public:
	vector<string> removeInvalidParentheses(string s) 
	{
		vector<string> res;
		map<string, bool> hash;
		int mindep = 2147483647;
		queue<pair<string, int>> Q;
		Q.push(make_pair(s, 0));
		hash[s] = 1;
		while (!Q.empty())
		{
			auto cur = Q.front(); Q.pop();
			if (isValid(cur.first))
			{
				res.push_back(cur.first);
				mindep = cur.second;
			}
			if (cur.second + 1 < mindep)
				for (int i = 0; i < cur.first.size(); ++i)
				{
                    if (isalpha(cur.first[i])) continue;
					string tmp = cur.first;
					string next = tmp.erase(i, 1);
					if (hash[next] == 0)
					{
						hash[next] = 1;
						Q.push(make_pair(next, cur.second + 1));
					}
				}
		}
		return res;
	}
};