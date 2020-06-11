/* 34. Find First and Last Position of Element in Sorted Array
Category: Medium
Problem Description:
    Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.
    Your algorithm's runtime complexity must be in the order of O(log n).
    If the target is not found in the array, return [-1, -1].
    Example 1:
        Input: nums = [5,7,7,8,8,10], target = 8
        Output: [3,4]
    Example 2:
        Input: nums = [5,7,7,8,8,10], target = 6
        Output: [-1,-1]
*/
class Solution
{
public:
    // An intuitive idea is to find the leftmost index and the rightmost index
    // through linear scan from left and from right respectively. However, the
    // time complexity of linear scan is O(n). Thus, we can just optimize it by
    // employ binary search to find both leftmost and rightmost indices.
    // Key difference with the vanilla binary search: if nums[mid] == target:
    // 1. when finding leftmost, update 'hi';
    // 2. when finding rightmost, update 'lo'.
    vector<int> searchRange(vector<int>& nums, int target)
    {
        if (nums.empty() || target < nums[0] || target > nums[nums.size() - 1])
            return vector<int>({ -1, -1 });
        auto leftmost = this->searchIndex(nums, 0, nums.size(), target, false);
        if (leftmost == nums.size() || nums[leftmost] != target)
            return vector<int>({ -1, -1 });
        auto rightmost = this->searchIndex(nums, leftmost, nums.size(), target, true) - 1;
        return vector<int>({ leftmost, rightmost });
    }

    // `mode`: indicate strategy to move the pointer (0 for finding leftmost, vice verse).
    int searchIndex(vector<int>& nums, int lo, int hi, int target, bool mode)
    {
        while (lo < hi)
        {
            auto mid = lo + (hi - lo) / 2;
            if (nums[mid] < target || (target == nums[mid] && mode)) lo = mid + 1;
            else hi = mid;
        }
        return lo;
    }
};