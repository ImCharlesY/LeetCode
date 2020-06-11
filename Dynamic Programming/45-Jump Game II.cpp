/* 45. Jump Game II
Category: Hard
Problem Description:
    Given an array of non-negative integers, you are initially positioned at the first index of the array.
    Each element in the array represents your maximum jump length at that position.
    Your goal is to reach the last index in the minimum number of jumps.
    Example:
        Input: [2,3,1,1,4]
        Output: 2
        Explanation: The minimum number of jumps to reach the last index is 2.
            Jump 1 step from index 0 to 1, then 3 steps to the last index.
*/
class Solution 
{
public:
#ifdef RECURSIVE_VERSION
    // Recursive Solution:
    // It is easy to solve this problem in a recursive manner. The problem can be decomposited into
    // sub-problems: step from 0 to i and find the minimum steps from i to the destination, where i
    // is selected from range [1, nums[0]].
    int _jump(const vector<int>& nums, int start)
    {
        if (start >= nums.size() - 1) return 0;
        int minimum_steps = INT_MAX;
        for (int step = 1; step <= nums[start]; ++step)
        {
            int next_steps = _jump(nums, start + step);
            if (next_steps == INT_MAX) continue;
            minimum_steps = std::min(minimum_steps, 1 + next_steps);
        }
        return minimum_steps;
    }

    int jump(vector<int>& nums)
    {
        return _jump(nums, 0);
    }
#endif // RECURSIVE_VERSION

#ifdef DYNAMIC_PROGRAMMING_VERSION
    // Dynamic Programming Solution:
    // Directly inspired by the recursive solution, we could define state d[i] as minimum steps
    // from i to the destination. Then the dynamic transition equation is d[i] = min(d[i], 1 + d[j]),
    // where j is selected from range [i + 1, i + nums[i]]. This solution has a time complexity between
    // O(n) and O(n^2), and a memory complexity of O(n).
    int jump(vector<int>& nums)
    {
        // dp[i] means the minimum steps from index i to the destination.
        vector<int> dp(nums.size(), INT_MAX);
        int maximum_pos = nums.size() - 1;
        dp[maximum_pos] = 0;
        for (int i = nums.size() - 2; i >= 0; --i)
        {
            for (int step = 1; step <= nums[i]; ++step)
            {
                int reach = std::min(maximum_pos, i + step);
                if (dp[reach] == INT_MAX) continue;
                dp[i] = std::min(dp[i], 1 + dp[reach]);
            }
        }
        return dp[0];
    }

    // 
    int jump(vector<int>& nums)
    {
        if (nums.size() <= 1) return 0;
        // dp[i] means the minimum steps from index 0 to index i.
        vector<int> dp(nums.size(), INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            if (i + nums[i] >= nums.size() - 1) return dp[i] + 1;
            for (int reach = i + 1; reach <= i + nums[i]; ++reach)
                dp[reach] = std::min(dp[reach], 1 + dp[i]);
        }
        return dp[nums.size() - 1];
    }

    int jump(vector<int>& nums)
    {
        if (nums.size() <= 1) return 0;
        // dp[i] means the minimum steps from index 0 to index i.
        vector<int> dp(nums.size(), INT_MAX);
        dp[0] = 0;
        int current_reach = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            int maximum_reach = i + nums[i];
            if (maximum_reach >= nums.size() - 1) return dp[i] + 1;
            if (maximum_reach > current_reach)
                for (; current_reach < maximum_reach; ++current_reach)
                    dp[current_reach + 1] = 1 + dp[i];
        }
        return dp[nums.size() - 1];        
    }
#endif // DYNAMIC_PROGRAMMING_VERSION

#ifdef BFS_VERSION
    int jump(vector<int>& nums)
    {
        int steps = 0, current_reach = 0, maximum_reach = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            maximum_reach = std::max(maximum_reach, i + nums[i]);
            if (i == current_reach)
            {
                ++steps;
                current_reach = maximum_reach;
            }
            if (current_reach >= nums.size() - 1) break;
        }
        return steps;
    }
#endif // BFS_VERSION
};