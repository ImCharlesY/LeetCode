class Solution 
{
	stack<int> st;
public:
	bool find132pattern(vector<int>& nums) 
	{
		if (nums.size() < 3) return 0;
		vector<int> minarr(nums.size());
		minarr[0] = nums[0];
		for (size_t i = 1; i < nums.size(); ++i)
			minarr[i] = min(minarr[i - 1], nums[i]);
		for (int i = nums.size() - 1; i >= 0; --i)
			if (nums[i] > minarr[i])
			{
				while (!st.empty() && st.top() <= minarr[i]) st.pop();
				if (!st.empty() && st.top() < nums[i]) return 1;
				st.push(nums[i]);
			}
		return 0;
	}
};