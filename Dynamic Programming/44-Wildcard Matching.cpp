class Solution 
{
public:
    bool isMatch_Recursion_ver(const string &s, const string &p) 
    {
		if (p.empty()) return s.empty();
		
		// If the first character is not a star, we match the first character and 
		// let both text and pattern move on one step.
		if (p[0] != '*')
		{
			bool preMatch = (!s.empty()) && (p[0] == '?' || s[0] == p[0]);
			return preMatch && isMatch_Recursion_ver(s.substr(1), p.substr(1));
		}
		// If a star is present in the pattern, we may delete a matched sequence in 
		// text and check if the rest of the text matches the pattern. 
		else
		{
			bool judge = 0;
			for (size_t i = 0; i <= s.size(); ++i)
				judge = judge || isMatch_Recursion_ver(s.substr(i), p.substr(1));
			return judge;
		}

    }

    bool isMatch_DP_ver(const string &s, const string &p)
    {
		// We just use an array to store results of the calls isMatch(s[i:], p[j:]).
		// dp[i][j] means the matching result of isMatch(s[i:], p[j:]).
		vector<vector<bool>> dp(s.size() + 1, vector<bool>(p.size() + 1, 0));

		// The following for loop initialize the dp array.
		// In this case, both text and pattern are empty.
		dp[s.size()][p.size()] = 1;				
		// The follows initialize first row.
		for (int j = p.size() - 1; j >= 0; --j)
			if (p[j] == '*') dp[s.size()][j] = 1;
			else break;

		// Recursion
		for (int i = s.size() - 1; i >= 0; --i)
			for (int j = p.size() - 1; j >= 0; --j)
			{
				// If the first character is not a star, we match the first character and 
				// let both text and pattern move on one step.
				if (p[j] == '?' || s[i] == p[j])
					dp[i][j] = dp[i + 1][j + 1];
				// If the first character is a star, there are 2 matched cases:
				// first, dp[i+1][j] means that * acts like any sequences;
				// second, dp[i][j+1] means that * acts like an empty sequence.
				else if (p[j] == '*')
					dp[i][j] = dp[i + 1][j] || dp[i][j + 1];
				else
					dp[i][j] = 0;
			}

		return dp[0][0];
    }

    bool isMatch(string s, string p)
    {
    	return isMatch_DP_ver(s, p);
    }
};