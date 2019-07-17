class Solution 
{
public:
	int trap(vector<int>& height) 
	{
        if (height.size() == 0) return 0;
        
		int res = 0;
		vector<int> left_max(height.size()), right_max(height.size());

		left_max[0] = height[0];
		for (size_t i = 1; i < height.size(); ++i) left_max[i] = max(left_max[i - 1], height[i]);

		right_max[height.size() - 1] = height[height.size() - 1];
		for (int i = height.size() - 2; i >= 0; --i) right_max[i] = max(right_max[i + 1], height[i]);

		for (size_t i = 0; i < height.size(); ++i) res += min(left_max[i], right_max[i]) - height[i];

		return res;
	}
};