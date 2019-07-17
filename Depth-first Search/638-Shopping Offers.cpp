class Solution
{
	int num;
	int dfs(const vector<int>& price, const vector<vector<int>>& special, vector<int>& needs)
	{
		int res = 0;
		for (int i = 0; i < num; ++i) res += price[i] * needs[i];
		for (auto &s : special)
		{
			auto clone = needs;
			int i = 0;
			for (; i < num; ++i)
			{
				int rest = clone[i] - s[i];
				if (rest < 0) break;
				clone[i] = rest;
			}
			if (i == num) res = min(res, s[i] + dfs(price, special, clone));
		}
		return res;
	}
public:
	int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs)
	{
		num = price.size();
		return dfs(price, special, needs);
	}
};