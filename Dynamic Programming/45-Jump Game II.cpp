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
    //  if (curidx + nums[curidx] >= this->steps) return 1;

    //  int minsteps = this->steps;

    //     for (size_t i = 1; i <= nums[curidx]; ++i)
    //     {
    //      int tmpsteps = 1 + helper(nums, curidx + i);
    //      if (tmpsteps < minsteps) minsteps = tmpsteps;
    //     }

    //     return minsteps;
    // }

    // DP - TLE (91/92)
    // int jump(vector<int>& nums) 
    // {
    //     if (nums.size() <= 1) return 0;
    //  // dp[i] means the minimum steps from index 0 to index i
    //  vector<int> dp(nums.size(), INT_MAX);
    //     dp[0] = 0;
    //  for (size_t i = 0; i < nums.size(); ++i)
    //  {
    //         if (i + nums[i] >= nums.size() - 1) return dp[i] + 1;
    //         // if we have determined the minimum steps to index i,
    //         // we can determine the upper bound of steps to index from i to i+nums[i].
    //         for (size_t j = i + 1; j <= i + nums[i]; ++j)
    //             dp[j] = min(dp[j], dp[i] + 1);
    //  }
    //  return 0;
    // }


    // DP
    // In fact, if dp[j] is already visited, dp[i] + 1 must be greater than or equal to dp[j],
    // thus we dont need to check those that are already reached.
    int jump(vector<int>& nums) 
    {
        if (nums.size() <= 1) return 0;
        // dp[i] means the minimum steps from index 0 to index i
        vector<int> dp(nums.size(), INT_MAX);
        dp[0] = 0;
        size_t reach = 0;
        for (size_t i = 0; i < nums.size(); ++i)
        {
            size_t newreach = i + nums[i];
            if (newreach >= nums.size() - 1) return dp[i] + 1;
            // if we have determined the minimum steps to index i,
            // we can determine the upper bound of steps to index from i to i+nums[i].
            if (newreach > reach)
            {
                for (++reach; reach <= newreach; ++reach)
                    dp[reach] = dp[i] + 1;
                --reach;
            }
        }
        return 0;
    }    
};