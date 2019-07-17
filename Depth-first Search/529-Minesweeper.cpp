class Solution 
{
public:
	vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) 
	{
		if (board[click.front()][click.back()] == 'M')
		{
			board[click.front()][click.back()] = 'X';
			return board;
		}
		int rLen = board.size(), cLen = board[0].size();
		queue<pair<int, int>> Q;
		Q.push(make_pair(click.front(), click.back()));
		while (!Q.empty())
		{
			auto cur = Q.front(); Q.pop();
			if (board[cur.first][cur.second] != 'E')continue;
			vector<pair<int, int>> neighbors = {
				make_pair(cur.first - 1,cur.second - 1),make_pair(cur.first - 1,cur.second),
				make_pair(cur.first - 1,cur.second + 1),make_pair(cur.first,cur.second - 1),
				make_pair(cur.first,cur.second + 1),make_pair(cur.first + 1,cur.second - 1),
				make_pair(cur.first + 1,cur.second),make_pair(cur.first + 1,cur.second + 1)
			};
			int cnt = 0;
			for (auto &neighbor : neighbors)
				if (neighbor.first >= 0 && neighbor.first < rLen&&neighbor.second >= 0 && neighbor.second < cLen&&board[neighbor.first][neighbor.second] == 'M') ++cnt;
			if (cnt) board[cur.first][cur.second] = '0' + cnt;
			else
			{
				board[cur.first][cur.second] = 'B';
				for (auto &neighbor : neighbors)
					if (neighbor.first >= 0 && neighbor.first < rLen&&neighbor.second >= 0 && neighbor.second < cLen)
						Q.push(neighbor);
			}
		}
		return board;
	}
};