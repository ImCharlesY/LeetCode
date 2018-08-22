class Solution 
{
public:
    bool isScramble(string s1, string s2) 
    {
    	// Divide string into 2 substrings with length i and n - k
    	// and check if the 2 substrings s1[0:i-1] and s1[i:] are the
    	// scrambles of s2[0:i-1] and s2[i:] or s2[n-i:] and s2[0:n-i-1].
    	
    	/*Recursion version:
    	if (s1 == s2) return 1;
		for (size_t i = 0; i < n; ++i)
			return 
			(isScramble(s1.substr(0,i), s2.substr(0,i)) & isScramble(s1.substr(i,n-i), s2.substr(i,n-i)))
			| 
			(isScramble(s1.substr(0,i), s2.substr(n-i,i)) & isScramble(s1.substr(i,n-i), s2.substr(0,n-i)));
    	*/
       	
       	// We implements DP method as follows.
       	// dp[len][i][j] means whether s1[i:i+len-1] is a scramble of s2[j:j+len-1].

       	size_t sLen = s1.size();
       	if (sLen == 0) return 1;
       	if (sLen == 1) return s1 == s2;

       	vector<vector<vector<char>>> dp(sLen+1, vector<vector<char>>(sLen, vector<char>(sLen, 0)));

       	for (size_t i = 0; i < sLen; ++i)
       		for (size_t j = 0; j < sLen; ++j)
       			dp[1][i][j] = (s1[i] == s2[j]);

       	for (size_t len = 2; len <= sLen; ++len)
       		for (size_t i = 0; i <= sLen - len; ++i)
       			for (size_t j = 0; j <= sLen - len; ++j)
       				for (size_t k = 1; k < len && !dp[len][i][j]; ++k)
       					dp[len][i][j] |= ((dp[k][i][j] & dp[len-k][i+k][j+k]) | (dp[k][i+len-k][j] & dp[len-k][i][j+k]));

       	return dp[sLen][0][0];
    }
};