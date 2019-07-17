class Solution 
{
public:
	int largestRectangleArea(vector<int>& heights) 
	{
		size_t maxArea = 0;
		heights.insert(heights.begin(), 0);
		heights.push_back(0);
		int index;
		stack<int> st;
		for (size_t i = 0; i < heights.size(); i++)
		{
			while (!st.empty() && heights[i] < heights[index = st.top()])
			{
				st.pop();
				maxArea = max(maxArea, heights[index] * (i - st.top() - 1));
			}
			st.push(i);
		}
		heights.erase(heights.begin());
		heights.pop_back();
		return maxArea;
	}
};