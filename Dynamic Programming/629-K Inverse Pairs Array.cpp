class Solution 
{
public:
    int kInversePairs(int n, int k) 
    {
    	if(k==0) return 1;
        vector<vector<int>> dp(n+1,vector<int>(k+1,0));
        int modulo = 1000000007;
        for(int i=1;i<=n;++i)
        	for(int j=0;j<=k;++j)
        		if(j==0) dp[i][j]=1;
        		else
        			dp[i][j]=(dp[i][j-1]+(dp[i-1][j]+modulo-((j-i)>=0?dp[i-1][j-i]:0))%modulo)%modulo;
        return (dp[n][k]+modulo-dp[n][k-1])%modulo;
    }
};