/* 47. Permutations II
Category: Medium
Problem Description:
    Given a collection of numbers that might contain duplicates, return all possible unique permutations.
    Example:
        Input: [1,1,2]
        Output:
        [
            [1,1,2],
            [1,2,1],
            [2,1,1]
        ]
*/
class Solution
{
    // The key issue is how to avoid duplicates.
    void _permuteUnique(vector<int> nums, int start, vector<vector<int>>& result)
    {
        // Use ge instead of e here in case of empty array. Cast nums.size() from size_t
        // to int to prevent underflow.
        if (start >= (int)nums.size() - 1) result.push_back(nums);
        else
            for (size_t i = start; i < nums.size(); ++i)
            {
                if (i != start && nums[i] == nums[start]) continue;
                std::swap(nums[start], nums[i]);
                _permuteUnique(nums, start + 1, result);
            }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums)
    {
        vector<vector<int>> result;
        std::sort(nums.begin(), nums.end());
        _permuteUnique(nums, 0, result);
        return result;
    }
};