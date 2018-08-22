class Solution 
{
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) 
    {
    	// Assume that we have two array named A and B with lengths of m and n.
    	// We need to divide all elements into two parts with equal length, while the left part
    	// is always less than the right part.
    	// So wo just need to do a binary search.
    	// Search i in [0,m], so that A[i - 1] <= B[j] and A[i] >= B[j - 1], where j = (m + n + 1) / 2 - i.
    	// Notice that in order to make sure that j is non-negative, m must less than n.
    	// For border condition, if i = 0, i = m, or j = 0, j = n, then we dont need to check the relations 
    	// between A[i - 1], B[j], A[i] and B[j - 1].
    	size_t m = nums1.size();
    	size_t n = nums2.size();
    	if (m > n)  return findMedianSortedArrays(nums2, nums1);
    	size_t imin = 0, imax = m;
    	size_t hlfLen = (m + n + 1) >> 1;
        
    	// Begin binary search
    	while (imin <= imax)
    	{
    		size_t i = (imin + imax) >> 1;
    		size_t j = hlfLen - i;
    		if (i < imax && nums1[i] < nums2[j - 1]) imin = i + 1;
    		else if (i > imin && nums1[i - 1] > nums2[j]) imax = i - 1;
    		else
    		{
    			int maxLeft = 0;
    			if (i == 0) maxLeft = nums2[j - 1];
    			else if (j == 0) maxLeft = nums1[i - 1];
    			else maxLeft = std::max(nums1[i - 1], nums2[j - 1]);

    			if ((m + n) & 1) return maxLeft;

    			int minRight = 0;
    			if (i == m) minRight = nums2[j];
    			else if (j == n) minRight = nums1[i];
    			else minRight = std::min(nums1[i], nums2[j]);

    			return (maxLeft + minRight) * 0.5;
    		}
    	}
    }
};