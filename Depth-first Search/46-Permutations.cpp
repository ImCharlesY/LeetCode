/* 46. Permutations
Category: Medium
Problem Description:
    Given a collection of distinct integers, return all possible permutations.
    Example:
        Input: [1,2,3]
        Output:
        [
          [1,2,3],
          [1,3,2],
          [2,1,3],
          [2,3,1],
          [3,1,2],
          [3,2,1]
        ]
*/
class Solution
{
    void _permute(vector<int>& nums, int start, vector<vector<int>>& result)
    {
        if (start == nums.size() - 1) result.push_back(nums);
        else
            for (size_t i = start; i < nums.size(); ++i)
            {
                std::swap(nums[start], nums[i]);
                _permute(nums, start + 1, result);
                std::swap(nums[i], nums[start]);
            }
    }
public:
    vector<vector<int>> permute(vector<int>& nums)
    {
        vector<vector<int>> result;
        _permute(nums, 0, result);
        return result;
    }
};