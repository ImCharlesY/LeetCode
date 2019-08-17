class Solution
{
public:
	// Key idea: linearly scan the sorted array, fix current position and use two pointers
	//           method to search other two positions.
	// 1. sort the array; (O(nlgn) if using quick sort)
	// 2. fix the value at current position during linear scanning, denoted as a (at index i);
	// 3. apply two pointers method to the sub-array exclude elements whose index are less than i:
	//    3.1. initialize two pointers j and k to the beginning and end of the sub-array, i.e., j = i + 1, k = len(array) - 1;
	//    3.2. if array[j] + array[k] == -array[i], that is a candidate;
	//    3.3. else array[j] + array[k] < -array[i], we should move pointer j rightward to increase array[j];
	//    3.4. else array[j] + array[k] > -array[i], we should move pointer k leftward to decrease array[k];
	//    3.5. repeat 3.2-3.4 until two pointers meet.
	vector<vector<int>> threeSum(vector<int>& nums) 
	{
		vector<vector<int>> results;
		auto len = nums.size();
		if (len < 3) return results;

		// first sort the array
		sort(nums.begin(), nums.end());
		// linearly scan the sorted array
		for (size_t i = 0; i < len - 2; ++i)
		{
			// ignore some special cases
			if (nums[i] + nums[len - 2] + nums[len - 1] < 0) continue; // nums[i] is too small
			if (nums[i] + nums[i + 1] + nums[i + 2] > 0) break;        // nums[i] is too large
			if (i > 0 && nums[i] == nums[i - 1]) continue; // avoid duplicates
			
			// fix element at index i
			auto fix = nums[i];
			// initialize two pointers
			size_t j = i + 1, k = len - 1;
			while (j < k)
			{
				if (nums[j] + nums[k] < -nums[i]) ++j;
				else if (nums[j] + nums[k] > -nums[i]) --k;
				else
				{
					results.push_back(vector<int>({ nums[i], nums[j], nums[k] }));
					// avoid duplicates
					++j, --k;
					while (nums[j] == nums[j - 1] && j < k) ++j;
					while (nums[k] == nums[k + 1] && j < k) --k;
				}
			}
		}

		return results;
	}
};