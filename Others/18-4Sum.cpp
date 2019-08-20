class Solution
{
public:
	// Key idea: Similar to 15.3Sum, linearly scan the sorted array, fix the first two positions 
	//           and use two pointers method to search other two positions.
	vector<vector<int>> fourSum(vector<int>& nums, int target)
	{
		vector<vector<int>> results;
		auto len = nums.size();
		if (len < 4) return results;

		// first sort the array
		sort(nums.begin(), nums.end());
		// linearly scan the sorted array
		for (size_t i = 0; i < len - 3; ++i)
		{
			// ignore some special cases
			if (nums[i] + nums[len - 3] + nums[len - 2] + nums[len - 1] < target) continue; // nums[i] is too small
			if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) break;          // nums[i] is too large
			if (i > 0 && nums[i] == nums[i - 1]) continue; // avoid duplicates

			for (size_t j = i + 1; j < len - 2; ++j)
			{
				// ignore some special cases
				if (nums[i] + nums[j] + nums[len - 2] + nums[len - 1] < target) continue;   // nums[j] is too small
				if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target) break;          // nums[j] is too large
				if (j > i + 1 && nums[j] == nums[j - 1]) continue; // avoid duplicates
				// initialize two pointers
				size_t k = j + 1, m = len - 1;
				while (k < m)
				{
					if (nums[i] + nums[j] + nums[k] + nums[m] < target) ++k;
					else if (nums[i] + nums[j] + nums[k] + nums[m] > target) --m;
					else
					{
						results.push_back(vector<int>({ nums[i], nums[j], nums[k], nums[m] }));
						// avoid duplicates
						++k, --m;
						while (nums[k] == nums[k - 1] && k < m) ++k;
						while (nums[m] == nums[m + 1] && k < m) --m;
					}
				}
			}
		}

		return results;
	}
};