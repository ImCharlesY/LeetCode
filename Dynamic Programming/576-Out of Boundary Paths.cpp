class Solution
{
public:
	int findPaths(int m, int n, int N, int i, int j)
	{
		vector<vector<vector<uint>>> dp(N + 1, vector<vector<uint>>(m, vector<uint>(n, 0)));
        for(int s = 1; s <= N; ++s)
            for(int x = 0; x < m; ++x)
                for(int y = 0; y < n; ++y)
                    dp[s][x][y] = 
                    (
                        (x == 0 ? 1 : dp[s - 1][x - 1][y]) 
                        +
                        (x == m - 1 ? 1 : dp[s - 1][x + 1][y])
                        + 
                        (y == 0 ? 1 : dp[s - 1][x][y - 1]) 
                        + 
                        (y == n - 1 ? 1 : dp[s - 1][x][y + 1])
                    )
                    % 1000000007;
		return dp[N][i][j];
	}
};