/* 39. Combination Sum
Category: Medium
Problem Description:
    Given a set of candidate numbers (candidates) (without duplicates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.
    The same repeated number may be chosen from candidates unlimited number of times.
    Note:
        All numbers (including target) will be positive integers.
        The solution set must not contain duplicate combinations.
    Example 1:
        Input: candidates = [2,3,6,7], target = 7,
        A solution set is:
        [
          [7],
          [2,2,3]
        ]
    Example 2:
        Input: candidates = [2,3,5], target = 8,
        A solution set is:
        [
          [2,2,2,2],
          [2,3,3],
          [3,5]
        ]
*/
class Solution
{
public:
    // 0-1 bag problem
#ifdef V1
    vector<vector<int>> combinationSum(vector<int>& candidates, int target)
    {
        sort(candidates.begin(), candidates.end());
        return this->_combinationSum(candidates, 0, target);
    }

    vector<vector<int>> _combinationSum(vector<int>& candidates, size_t start, int target)
    {
        vector<vector<int>> res;
        for (size_t i = start; i < candidates.size(); ++i)
        {
            auto can = candidates[i];
            vector<vector<int>> sols;
            if (target < can) break;
            else if (target == can) sols.push_back(vector<int>{can});
            else
            {
                sols = this->_combinationSum(candidates, i, target - can);
                if (!sols.empty()) for (auto& sol : sols) sol.push_back(can);
            }
            res.insert(res.end(), sols.begin(), sols.end());
        }
        return res;
    }
#endif // V1
#ifdef V2
    vector<vector<int>> combinationSum(vector<int>& candidates, int target)
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
            for (size_t i = start; i < candidates.size(); ++i)
            {
                auto can = candidates[i];
                if (target < can) break;
                path.push_back(can);
                this->_combinationSum(candidates, target - can, i, path, result);
                path.pop_back();
            }
    }
#endif //V2
};