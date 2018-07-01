class Solution
{
public:
	int removeBoxes(vector<int>& boxes)
	{
		int n = boxes.size();
		vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n, 0)));
        /*
        dp[i][j][k] denotes the maximum points possible by removing the boxes of subarray boxes[i, j] with k boxes attached to its left of      
        the same color as boxes[i] 
        */

		for (int i = 0; i < n; ++i)
			for (int j = 0; j <= i; ++j)
				dp[i][i][j] = (j + 1)*(j + 1);

		for (int len = 1; len < n; ++len)
			for (int i = 0; i < n - len; ++i)
			{
				int j = i + len;
				for (int k = 0; k <= i; ++k)
				{
					dp[i][j][k] = (k + 1)*(k + 1) + dp[i + 1][j][0];
					for (int m = i + 1; m <= j; ++m)
						if (boxes[m] == boxes[i])
							dp[i][j][k] = max(dp[i][j][k], dp[i + 1][m - 1][0] + dp[m][j][k + 1]);
				}
			}
		
		return dp[0][n - 1][0];
	}
};