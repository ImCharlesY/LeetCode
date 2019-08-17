class Solution
{
	void update(const int& newsum, const int& target, int& result, int& residual) const
	{
		result = (residual > abs(newsum - target)) ? newsum : result;
		residual = min(residual, abs(newsum - target));
	}
public:
	// Key idea: linearly scan the sorted array, fix current position and use two pointers
	//           method to search other two positions.
	// 1. sort the array; (O(nlgn) if using quick sort)
	// 2. fix the value at current position during linear scanning, denoted as a (at index i);
	// 3. apply two pointers method to the sub-array exclude elements whose index are less than i:
	//    3.1. initialize two pointers j and k to the beginning and end of the sub-array, i.e., j = i + 1, k = len(array) - 1;
	//    3.2. if array[i] + array[j] + array[k] == target, that is the best answer;
	//    3.3. else array[i] + array[j] + array[k] < target, we should move pointer j rightward to increase array[j];
	//    3.4. else array[i] + array[j] + array[k] > target, we should move pointer k leftward to decrease array[k];
	//    3.5. repeat 3.2-3.4 until two pointers meet.
	int threeSumClosest(vector<int>& nums, int target)
	{
		int result = target;
		int residual = INT_MAX;
		size_t len = nums.size();

		// first sort the array
		sort(nums.begin(), nums.end());
		// linearly scan the sorted array
		for (size_t i = 0; i < len - 2; ++i)
		{
			// initialize two pointers
			size_t j = i + 1, k = len - 1;
			while (j < k)
			{
				int newsum = nums[i] + nums[j] + nums[k];
				int newres = abs(newsum - target);
				if (newsum == target) return target;
				else if (newsum < target)
				{
					if (newres < residual) this->update(newsum, target, result, residual);
					++j;
				}
				else
				{
					if (newres < residual) this->update(newsum, target, result, residual);
					--k;
				}
			}
		}

		return result;
	}
};