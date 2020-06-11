/* 42. Trapping Rain Water
Category: Hard
Problem Description:
    Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.
    The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped. Thanks Marcos for contributing this image!
    Example:
        Input: [0,1,0,2,1,0,1,3,2,1,2,1]
        Output: 6
*/
class Solution 
{
public:
    // By decomposing the problem, the total water can be trapper in the elevation map is the summation
    // of water each bar can store on the top, which can be calculated as the difference between the
    // minimum of the maximum heights on both sides and the height of the current bar. Therefore, we have
    // following solutions.
    //
    // Naive Solution (Brute Force):
    // For each bar, find bars with maximum height on its both sides, and calculate the minimum difference
    // between those and the height of current bar. Then take the summation of the results of all bars.
    // The time complexity is O(n^2) since there exists a two-level loop: the outer loop iterates each bar
    // in the elevation map, while the inner loop iterates the whole elevation map again to search
    // bars with maximum heights on both sides for each bar. Besides, the space complexity is O(1).
    
#ifdef DYNAMIC_PROGRAMMING_VERSION
    // Dynamic Programming Solution:
    // In brute force solution, we iterate the array again and again just to find the highest bars.
    // In fact, this could be stored, since the procedure to find the maximum height of bar from left end
    // or right end upto current position can be recursive. That is, the 'left_max' of current position i
    // is the maximum between 'left_max' of position i - 1 and height of position i. Same rule applies to
    // the right side. Therefore, we need 3 iterations for finding left_max, right_max and result calculation
    // respectively. Time complexity is O(n) and space complexity is O(n).
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
#endif // DYNAMIC_PROGRAMMING_VERSION
#ifdef MONOTONE_STACK_VERSION
    // Monotone-stack Solution:
    // We can solve the problem from another perspective. The water each bar traps can be also defined
    // as the area bounded by current bar and its nearest higher bars (both sides). Therefore, we can
    // iterate the array from left end to right end to find such 'abc' patterns, where b < a and
    // b < c. The problem then becomes a special parenthese matching problem, that is, when a 'abc' pattern
    // matches, we are sure that the bar 'b' is bounded by 'a' and 'c', thus we can calculate the resulting
    // trapped water by (min(b, c) - a) * distance between 'a' and 'c'. After that, 'abc' can be replaced
    // with max(a, c) since bar 'b' no longer holds water (under the new definition). For matching problem,
    // we can use a stack to handle it. When iterating over the array, every time we get a new bar, we push
    // it into the stack, then we check whether a pattern 'abc' is matched at the tail of the stack. If matched,
    // those bars will be popped from the stack, replaced with max(a, c) and the resulting trapped water can
    // be computed and added to the final answer. Note that in this way, we in fact maintain a monotone
    // descending stack. Time and space complexities are both O(n).
    int trap(vector<int>& height)
    {
        if (height.size() == 0) return 0;

        int res = 0;
        // Initialize a monotone descending stack
        stack<int> st;
        // Iterate the array
        for (size_t i = 0; i < height.size(); ++i)
        {
            // For each bar, we check whether it is smaller than or equal to the bar at the top
            // of stack, which means the current bar is bounded by the previous bars in the stack.
            // If a bar longer than that at the top is found, then a 'abc' pattern is matched, i.e.,
            // the bar at the top is bounded by the current bar and a previous bar in the stack.
            while (!st.empty() && height[i] > height[st.top()])
            {
                int mid = st.top();
                st.pop();
                if (st.empty()) break;
                int left_bound = st.top();
                int distance = i - left_bound - 1;
                int bounded_height = std::min(height[i], height[left_bound]) - height[mid];
                res += distance * bounded_height;
            }
            st.push(i);
        }
        return res;
    }
#endif // MONOTONE_STACK_VERSION
#define TWO_POINTERS_VERSION
#ifdef TWO_POINTERS_VERSION
    // Two Pointers Solution:
    // From the dynamic programming solution, we maintain two arrays for left_max and right_max
    // recording, and calculate trapped water for each bar based on these two arrays. We can observe
    // that left_max array is ascending and right_max array is descending due to the recursive mechanism.
    // Therefore, if there is a bar at one end (say right or index j) that is high enough (height[i] < height[j]),
    // since that right_max[i] >= right_max[j] if i < j, we are sure that bar at i is bounded by bar
    // at j, and the water trapped would be dependant on height of bar in current direction (from left to right).
    // Similar rule applies to another direction.
    int trap(vector<int>& height)
    {
        if (height.size() == 0) return 0;

        int res = 0;
        int ptr_left = 0, ptr_right = height.size() - 1;
        int max_left = 0, max_right = 0;
        while (ptr_left < ptr_right)
        {
            // If there is a larger bar on the right, then bar at ptr_left may hold water
            if (height[ptr_left] < height[ptr_right])
            {
                // There exist three cases:
                // Case 1: max_left < height[ptr_left] < height[ptr_right],
                //      there is no higher bar to the left end, so current (ptr_left) bar cannot hold water.
                // Case 2: height[ptr_left] < max_left < height[ptr_right],
                //      there is a higher bar to the left end, and the amount of water depends on the bar to the
                //      left end.
                // Case 3: height[ptr_left] < height[ptr_right] < max_left,
                //      there is a higher bar to the left end, but it is higher than bar at ptr_right. The amount
                //      of water depends on the shorter side which is bar at ptr_right.
                //      However, this never gonna happen. Note that since we have moved ptr_left from position of
                //      max_left to current position. It indicates that sometime earlier, there must be some higher
                //      bar on the right side (bar at ptr_right or max_right) that is higher than max_left existed.
                height[ptr_left] > max_left ? max_left = height[ptr_left] : res += (max_left - height[ptr_left]);
                ++ptr_left;
            }
            else
            {
                height[ptr_right] > max_right ? max_right = height[ptr_right] : res += (max_right - height[ptr_right]);
                --ptr_right;
            }
            
        }
        return res;
    }
#endif // TWO_POINTERS_VERSION
};