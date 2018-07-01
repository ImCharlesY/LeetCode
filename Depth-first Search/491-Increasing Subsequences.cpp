class Solution
{
	set<vector<int>> res;
	vector<int> tmpContainer;
	void find(vector<int>& nums, int index)
	{
		if (tmpContainer.size() > 1) res.insert(tmpContainer);
		for (int i = index; i < nums.size(); ++i)
			if (tmpContainer.size() == 0 || tmpContainer.back() <= nums[i])
			{
				tmpContainer.push_back(nums[i]);
				find(nums, i + 1);
				tmpContainer.pop_back();
			}
	}
public:
	vector<vector<int>> findSubsequences(vector<int>& nums)
	{
		find(nums, 0);
		return vector<vector<int>>(res.begin(), res.end());
	}
};