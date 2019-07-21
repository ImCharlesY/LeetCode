class Solution 
{
public:
    vector<int> twoSum(vector<int>& nums, int target) 
    {
        std::map<int, int> hashtbl;
        for (int idx = 0; idx < nums.size(); ++idx)
        {
            if (hashtbl.find(target - nums[idx]) != hashtbl.end())
            {
                int oidx = hashtbl[target - nums[idx]];
                return (idx < oidx) ? std::vector<int>({idx, oidx}) : std::vector<int>({oidx, idx});
            }
            hashtbl[nums[idx]] = idx;
        }
        return std::vector<int>();
    }
};