/* 40. Combination Sum II
Category: Medium
Problem Description:
    Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.
    Each number in candidates may only be used once in the combination.
    Note:
        All numbers (including target) will be positive integers.
        The solution set must not contain duplicate combinations.
    Example 1:
        Input: candidates = [10,1,2,7,6,1,5], target = 8,
        A solution set is:
        [
          [1, 7],
          [1, 2, 5],
          [2, 6],
          [1, 1, 6]
        ]
    Example 2:
        Input: candidates = [2,5,2,1,2], target = 5,
        A solution set is:
        [
          [1,2,2],
          [5]
        ]
*/
class Solution
{
public:
    // Similar to P39, but we need to skip duplicate candidates.
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
    {
        sort(candidates.begin(), candidates.end());
        vector<int> path;
        vector<vector<int>> result;
        this->_combinationSum(candidates, target, 0, path, result);
        return result;
    }

    void _combinationSum(vector<int>& candidates, int target, size_t start, vector<int>& path, vector<vector<int>>& result)
    {
        if (target == 0) result.push_back(path);
        else
            for (size_t i = start; i < candidates.size(); )
            {
                auto can = candidates[i];
                if (target < can) break;
                path.push_back(can);
                this->_combinationSum(candidates, target - can, i + 1, path, result);
                path.pop_back();
                while (++i < candidates.size() && candidates[i] == can);
            }
    }
};