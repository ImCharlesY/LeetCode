class Solution
{
public:
    // Algorithm: DP
    // dp[i][j], 0<=i<ring_len,0<=j<key_len, means the minimum steps to get key[j] starting at ring[i].
    // Thus we have the transition fomula -- dp[i][j]=min(dp[i][j],step+dp[k][j+1]), 
    // while step is the length of path from ring[i] to ring[k], so that ring[k] == key[j] 
    int findRotateSteps(string ring, string key)
    {
        // Construct a dictionary for searching.
        map<char, vector<int>> ring_pos;
        for (size_t i = 0; i<ring.size(); ++i)
            ring_pos[ring[i]].push_back(i);

        int ring_len = ring.size();
        int key_len = key.size();

        vector<vector<int>> dp(ring_len,vector<int>(key_len+1,0));

        for(int j=key_len-1;j>=0;--j)
            for(int i=0;i<ring_len;++i)
            {
                dp[i][j]=INT_MAX;
                for(auto idx:ring_pos[key[j]])
                {
                    int steps=abs(idx-i);
                    dp[i][j]=min(dp[i][j],min(steps,ring_len-steps)+dp[idx][j+1]);
                }
            }
        return dp[0][0]+key_len;
    }
};