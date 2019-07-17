class Solution 
{
public:
    bool isMatch_Recursion_ver(const string &s, const string &p) 
    {
		if (p.empty()) return s.empty();
		
		// Check if the first character matched.
		bool preMatch = (!s.empty()) && (p[0] == '.' || s[0] == p[0]);

		// If a star is present in the pattern, we may ignore this part of the pattern which
		// means that this part of pattern repeats zero time in text, or just delete a matching
		// character in text and check if the rest of the text matches the pattern. 
		if (p.size() >= 2 && p[1] == '*')
			return isMatch(s, p.substr(2)) || preMatch && isMatch(s.substr(1), p);
		// If there is no a star present in the pattern, both text and pattern move on one step.
		else
			return preMatch && isMatch(s.substr(1), p.substr(1));
    }

    bool isMatch_DP_ver(const string &s, const string &p)
    {
		// We just use an array to store results of the calls isMatch(s[i:], p[j:]).
		// dp[i][j] means the matching result of isMatch(s[i:], p[j:]).
		vector<vector<bool>> dp(s.size() + 1, vector<bool>(p.size() + 1, 0));

		dp[s.size()][p.size()] = 1;				// In this case, both text and pattern are empty.
		for (int i = s.size(); i >= 0; --i)
			for (int j = p.size() - 1; j >= 0; --j)
			{
				bool preMatch = (i < s.size()) && (p[j] == '.' || s[i] == p[j]);
				if (j + 1 < p.size() && p[j + 1] == '*')
					dp[i][j] = dp[i][j + 2] || preMatch && dp[i + 1][j];
				else
					dp[i][j] = preMatch && dp[i + 1][j + 1];
			}

		return dp[0][0];
    }

    bool isMatch(string s, string p)
    {
    	return isMatch_DP_ver(s, p);
    }
};