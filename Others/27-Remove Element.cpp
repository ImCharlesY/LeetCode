class Solution
{
public:
	int removeElement(vector<int>& nums, int val)
	{
		int idx = -1;
		for (size_t i = 0; i < nums.size(); ++i)
		{
			if (nums[i] == val) continue;
			nums[++idx] = nums[i];
		}
		return idx + 1;
	}
};