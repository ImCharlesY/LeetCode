/* 31. Next Permutation
Category: Medium
Problem Description:
    Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.
    If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).
    The replacement must be in-place and use only constant extra memory.
    Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
        1,2,3 → 1,3,2
        3,2,1 → 1,2,3
        1,1,5 → 1,5,1
*/
class Solution 
{
public:
    // Permutation can be generated in a recursive manner, that is:
    // given a set of numbers (denoted as 'P'), pick up one number (denoted as 'a')
    // from 'P' in an increasing order and arrange it at the first place of the permutation.
    // Then generate permutation on the rest of the numbers (i.e., given 'P\{a}').
    // Here we can find that when the rest of the numbers ('P\{a}') arrive at their largest
    // possible permutation (in a decreasing order), it is time for the element at the first
    // place of the permutation moves to 'next a'. The 'next a' is the element that is just
    // larger than 'a' in 'P' (or in 'P\{a}').
    //
    // Therefore, given a permutation to find the next permutation, we only need to find out
    // the largest decreasing sub-permutation from some position 'i' to the end of the permutation.
    // Then elements in array[i:end] arrive at their largest permutation, and element at array[i-1]
    // should be swapped with the just larger element in array[i:end], and finally, array[i:end]
    // should be sorted in increasing order.
    void nextPermutation(vector<int>& nums)
    {
        if (nums.empty()) return;
        // Find the first element that breaks the increasing order from the tail of the array.
        auto cur_head_iter = std::is_sorted_until(nums.rbegin(), nums.rend());
        if (cur_head_iter != nums.rend())
        {
            // Find the first element that just larger than *cur_head_iter among elements lying to the
            // right of cur_head_iter.
            auto next_head_iter = std::upper_bound(nums.rbegin(), cur_head_iter, *cur_head_iter);
            // Swap elements.
            std::iter_swap(cur_head_iter, next_head_iter);
        }
        // Sort the subarray lying to the right of current head element in increasing order (smallest permutation).
        std::reverse(nums.rbegin(), cur_head_iter);
    }
};