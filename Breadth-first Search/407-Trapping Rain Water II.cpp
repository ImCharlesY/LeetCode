class Solution
{
public:
	int trapRainWater(vector<vector<int>>& heightMap)
	{
		if (heightMap.size() == 0) return 0;
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
		int row = heightMap.size(), col = heightMap[0].size();
		vector<vector<int>> visited(row, vector<int>(col, 0));
		int ans = 0, MaxH = INT_MIN;
		for (int i = 0; i < row; ++i)
			for (int j = 0; j < col; ++j)
			{
				if (!(i == 0 || j == 0 || i == row - 1 || j == col - 1)) continue;
				Q.push(make_pair(heightMap[i][j], i * col + j));
				visited[i][j] = 1;
			}
		vector<vector<int>> dir{ { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 } };
		while (!Q.empty())
		{
			auto cur = Q.top(); Q.pop();
			int x = cur.second / col, y = cur.second % col;
			MaxH = max(MaxH, cur.first);
			for (auto d : dir)
			{
				int x1 = x + d[0], y1 = y + d[1];
				if (x1 < 0 || y1 < 0 || x1 > row - 1 || y1 > col - 1 || visited[x1][y1]) continue;
				visited[x1][y1] = 1;
				if (heightMap[x1][y1] < MaxH) ans += MaxH - heightMap[x1][y1];
				Q.push(make_pair(heightMap[x1][y1], x1 * col + y1));
			}
		}
		return ans;
	}
};