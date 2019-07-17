class Solution 
{
	const vector<vector<int>> dir = { {-1,0},{1,0},{0,-1},{0,1} };
    int row, col;
	int dfs(vector<vector<int>>& matrix, int i, int j, vector<vector<int>>& cache)
	{
		if (cache[i][j]) return cache[i][j];
		int len = 1;
		for (auto &d : dir)
		{
			int x = i + d[0], y = j + d[1];
			if (x < 0 || y < 0 || x >= row || y >= col || matrix[x][y] <= matrix[i][j]) continue;
			len = max(len, 1 + dfs(matrix, x, y, cache));
		}
		cache[i][j] = len;
		return len;
	}
public:
	int longestIncreasingPath(vector<vector<int>>& matrix) 
	{
		if (matrix.size() == 0) return 0;
		row = matrix.size(), col = matrix[0].size();
		vector<vector<int>> cache(row, vector<int>(col, 0));
		int res = 1;
		for(int i = 0; i < row; ++i)
			for (int j = 0; j < col; ++j)
				res = max(res, dfs(matrix, i, j, cache));
		return res;
	}
};