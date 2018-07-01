class Solution
{
	void BFS(vector<vector<char>>& grid, int x, int y)
	{
		queue<pair<int, int>> BFSQueue;
		BFSQueue.push(pair<int, int>(x, y));
		grid[x][y] = '0';
		while (!BFSQueue.empty())
		{
			auto cur = BFSQueue.front(); BFSQueue.pop();
			vector<pair<int, int>> next =
			{
				 pair<int, int>(cur.first + 1, cur.second), pair<int, int>(cur.first, cur.second + 1),
				 pair<int, int>(cur.first - 1, cur.second), pair<int, int>(cur.first, cur.second - 1)
			};
			for (auto &nextpos : next)
			{
				int nx = nextpos.first, ny = nextpos.second;
				if (nx >= 0 && nx < rLen && ny >= 0 && ny < cLen && grid[nx][ny] == '1')
				{
					grid[nx][ny] = '0';
					BFSQueue.push(nextpos);
				}
			}
		}
	}
	int rLen, cLen;
public:
	int numIslands(vector<vector<char>>& grid)
	{
		if (grid.size() == 0 || grid[0].size() == 0) return 0;

		rLen = grid.size(), cLen = grid[0].size();
		size_t cnt = 0;

		for (int x = 0; x < rLen; ++x)
			for (int y = 0; y < cLen; ++y)
				if (grid[x][y] == '1')
				{
					++cnt;
					BFS(grid, x, y);
				}

		return cnt;
	}
};