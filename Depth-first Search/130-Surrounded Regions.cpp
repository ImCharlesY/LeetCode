class Solution 
{
	void BFS(vector<vector<char>>& board, int x, int y)
	{
		queue<pair<int, int>> BFSQueue;
		board[x][y] = 'B';
		BFSQueue.push(make_pair(x, y));
		while (!BFSQueue.empty())
		{
			auto cur = BFSQueue.front();
			BFSQueue.pop();
			vector<pair<int, int>> next =
			{
				{ cur.first - 1,cur.second }, { cur.first + 1,cur.second },
				{ cur.first,cur.second - 1 }, { cur.first,cur.second + 1 }
			};
			for (auto &vec : next)
			{
				int nx = vec.first, ny = vec.second;
				if (nx >= 0 && nx < rLen && ny >= 0 && ny < cLen && board[nx][ny] == 'O')
				{
					board[nx][ny] = 'B';
					BFSQueue.push(make_pair(nx, ny));
				}
			}
		}
	}
	int cLen, rLen;
public:
	void solve(vector<vector<char>>& board)
	{
		if (board.size() == 0 || board[0].size() == 0) return;
		rLen = board.size(), cLen = board[0].size();
		for (int i = 0; i < rLen; i++)
		{
			if (board[i][0] == 'O') BFS(board, i, 0);
			if (board[i][cLen - 1] == 'O') BFS(board, i, cLen - 1);
		}
		for (int i = 0; i < cLen; i++)
		{
			if (board[0][i] == 'O') BFS(board, 0, i);
			if (board[rLen - 1][i] == 'O') BFS(board, rLen - 1, i);
		}
		for (auto &r : board)
			for (auto &i : r)
				if (i == 'O') i = 'X';
				else if (i == 'B') i = 'O';
	}
};