class Solution 
{
	int subset(vector<int>& nums,int s)
	{
		/*
		Let dp[s] means the num of subset of nums whose sum is the target s
		*/
		vector<int> dp(s + 1, 0);
		/*
		For each num of array nums, if current num can be an item of the subset, then
		dp[s] += dp[s - num]
        It is obviously that there is one subset whose sum is 0, empty set. So dp[0] = 1;
		*/
        dp[0] = 1;
		for (int num : nums)	
			for (int i = s; i >= num; --i)
				dp[i] += dp[i - num];
		return dp[s];
	}
public:
	/*
	Let set P be the positive subset of nums, set N be the negative subset
	original pro: sum(P) - sum(N) = target
	-> sum(P) + sum(N) + sum(P) - sum(N) = target + sum(P) + sum(N)
    -> 2 * sum(P) = target + sum(nums)
	So just find a positive subset which satisfies sum(P) == (target + sum(nums)) >> 1;
	BTW, it also means that the value of (target + sum(nums)) must be even
	*/
	int findTargetSumWays(vector<int>& nums, int S) 
	{
		int sum = accumulate(nums.begin(), nums.end(), 0);
		return (sum < S || (sum + S) & 1) ? 0 : subset(nums, (sum + S) >> 1);
	}
};
