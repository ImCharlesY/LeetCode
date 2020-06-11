/* 33. Search in Rotated Sorted Array
Category: Medium
Problem Description:
    Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
    (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
    You are given a target value to search. If found in the array return its index, otherwise return -1.
    You may assume no duplicate exists in the array.
    Your algorithm's runtime complexity must be in the order of O(log n).
    Example 1:
        Input: nums = [4,5,6,7,0,1,2], target = 0
        Output: 4
    Example 2:
        Input: nums = [4,5,6,7,0,1,2], target = 3
        Output: -1
*/
class Solution
{
public:
    // If the array is sorted, we can simply apply binary search to achieve O(log n).
    // However, the array is now rotated at some unknown pivot. An intuitive idea is
    // to find the privot then apply binary search to the two seperated subarrays.
    // Binary search can be also employed to find the privot.
#ifdef V1 // Version 1: employ two binary search.
    int search(vector<int>& nums, int target)
    {
        if (nums.empty()) return -1;
        if (nums.size() == 1) return (nums[0] == target) ? 0 : -1;
        // Find the privot.
        size_t left_end = 0, right_begin = nums.size() - 1;
        // For case that input array is not rotated.
        if (nums[left_end] < nums[right_begin])
            left_end = nums.size() - 1, right_begin = 0;
        else
        {
            while (left_end < right_begin - 1)
            {
                auto mid = (left_end + right_begin) / 2;
                if (nums[left_end] > nums[mid]) right_begin = mid;
                else left_end = mid;
            }
        }
        // Employ binary search.
        size_t length = nums.size();
        size_t left = right_begin, right = left_end;
        if (nums[left] > target || nums[right] < target) return -1;
        while (left <= right || (left > right && left >= right_begin && right <= left_end))
        {
            // Since our pointers 'left' and 'right' move cyclically, the border case should be tackled specially.
            if (left == right) return (nums[left] == target) ? left : -1;
            size_t mid = (left <= right) ? (left + right) / 2 : (left + right + length) % (2 * length) / 2;
            if (nums[mid] > target) right = (mid + length - 1) % length;
            else if (nums[mid] < target) left = (mid + 1) % length;
            else return mid;
        }
        return -1;
    }
#endif // V1
#ifdef V2 // Version 2: employ only one binary search.
    int search(vector<int>& nums, int target)
    {
        if (nums.empty()) return -1;
        int left = 0, right = nums.size() - 1;
        while (left <= right)
        {
            auto mid = (left + right) / 2;
            if (nums[mid] == target) return mid;
            else if (nums[left] <= nums[mid]) // if the privot is located in the right part.
            {
                if (nums[left] <= target && target <= nums[mid])
                    right = mid - 1;
                else
                    left = mid + 1;
            }
            else // if the privot is located in the left part.
            {
                if (nums[mid] <= target && target <= nums[right])
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }
        return -1;
    }
#endif // V2
};