class Solution 
{
    // Given an unsorted integer array, find the smallest missing positive integer.
    // Your algorithm should run in O(n) time and uses constant extra space.
public:
    int firstMissingPositive(vector<int>& nums) 
    {
        // For each positive number, place it at the position whose index is the same
        // as its value. In this way, after scanning the whole list, the first element
        // which has different index and value is what we need.
        if (nums.empty()) return 1;
        int length = nums.size();
        // First linear scan [O(n)] -- put all positive numbers in place.
        for (size_t i = 0; i < length; )
        {
            int value = nums[i];
            // We need to check current position again when sway happens
            if (value > 0 && value <= length && value != i + 1 && nums[value - 1] != value)
            {   // swap elements
                nums[i] = nums[value - 1];
                nums[value - 1] = value;
            }
            else ++i;
        }
        // Second linear scan [O(n)] -- find the first element with different index and value.
        for (size_t i = 0; i < length; ++i)
        {
            if (nums[i] != i + 1) return i + 1;
        }
        // if result not found in the second scan, it means all the numbers are put in place,
        // thus the target number is length + 1.
        // e.g. [test case 159]: input-[1], target-2
        return length + 1;
    }
};