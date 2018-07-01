class Solution
{
public:
	vector<string> findAllConcatenatedWordsInADict(vector<string>& words)
	{
		set<string> ans;
		set<string> pre;
		sort(words.begin(), words.end(), [](const string& l, const string& r) {return l.size() < r.size(); });
		for (auto &w : words)
		{
			int n = w.size();
            if (n == 0) continue;
			vector<int> dp(n + 1, 0);
			dp[0] = 1;
			for (int i = 1; i <= n; ++i)
				for (int j = 0; j < i; ++j)
				{
					if (dp[j] == 0) continue;
					if (pre.find(w.substr(j, i - j)) != pre.end())
					{
						dp[i] = 1;
						break;
					}
				}
			if (dp[n]) ans.insert(w);
			pre.insert(w);
		}
		return vector<string>(ans.begin(), ans.end());
	}
};