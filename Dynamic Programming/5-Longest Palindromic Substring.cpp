class Solution 
{
public:
    string longestPalindrome(string s) 
    {
        int start = 0, maxlen = 1;
		vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), 1));
		for (int len = 2; len <= s.size(); ++len)
			for (int i = 0; i <= s.size() - len; ++i)
			{
				int j = i + len - 1;
				dp[i][j] = (s[i] == s[j]) ? dp[i + 1][j - 1] : 0;
				if (dp[i][j]) start = i, maxlen = len;
			}
		return s.substr(start, maxlen);
    }
};