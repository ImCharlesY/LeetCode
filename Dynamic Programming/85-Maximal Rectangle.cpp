class Solution 
{
public:
	int maximalRectangle(vector<vector<char>>& matrix) 
	{
        if (matrix.size() == 0 || matrix[0].size() == 0) return 0;
        
		for (auto &i : matrix)
		{
			i.insert(i.begin(), '0');
			i.push_back('0');
		}
			
		size_t rLen = matrix.size(), cLen = matrix[0].size();
		size_t maximal = 0;
		vector<size_t> heights(cLen, 0);
		for (size_t row = 0; row < rLen; row++)
		{
			stack<size_t> st;
			st.push(0);
			for (size_t i = 0; i < cLen; i++)
			{
				heights[i] = (matrix[row][i] == '1') ? heights[i] + 1 : 0;
				size_t index;
				while (heights[i] < heights[index = st.top()])
				{
					st.pop();
					maximal = max(maximal, heights[index] * (i - st.top() - 1));
				}
				st.push(i);
			}
		}

		for (auto &i : matrix)
		{
			i.erase(i.begin());
			i.pop_back();
		}

		return maximal;
	}
};