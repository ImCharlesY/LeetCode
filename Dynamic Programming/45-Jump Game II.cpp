class Solution 
{
	size_t steps;
public:
	// Recursive
    // int jump(vector<int>& nums) 
    // {
    //     this->steps = nums.size() - 1;
    //     return helper(nums, 0);
    // }

    // int helper(std::vector<int>& nums, size_t curidx)
    // {
    // 	if (curidx + nums[curidx] >= this->steps) return 1;

    // 	int minsteps = this->steps;

    //     for (size_t i = 1; i <= nums[curidx]; ++i)
    //     {
    //     	int tmpsteps = 1 + helper(nums, curidx + i);
    //     	if (tmpsteps < minsteps) minsteps = tmpsteps;
    //     }

    //     return minsteps;
    // }

	// DP
    int jump(vector<int>& nums) 
    {
    	// dp[i] means the minmum steps from index 0 to index i
    	vector<int> dp(nums.size(), 0);
    	for (size_t i = 1; i < nums.size(); ++i)
    	{
    		dp[i] = INT_MAX;
    		for (size_t j = 0; j < i; ++j)
    			if (nums[j] >= i - j)
    				dp[i] = min(dp[i], dp[j] + 1);
    	}
    	return dp.back();
    }
};