class Solution 
{
	int rLen, cLen;
	map<pair<int, int>, int> hash;
	//hash表second值为一个位数组，
	//最低位表示是否访问，
	//第一位表示是否有左通路，
	//第二位表示是否有右通路,
	//第三位表示当前bfs中是否访问
	bool bfs(vector<vector<int>>& matrix, pair<int, int>& vec)
	{
		int flag = 0x0;
		map<pair<int, int>, int> curhash;
		queue<pair<int, int>> Q;
		curhash[vec] = 1;
		Q.push(vec);
		while (!Q.empty())
		{
			auto cur = Q.front(); Q.pop();
			if (cur.first == 0 || cur.second == 0) flag |= (0x1 << 0);
			if (cur.first == rLen - 1 || cur.second == cLen - 1) flag |= (0x1 << 1);
			if (flag == 0x3) break;
			vector<pair<int, int>> nexts = { make_pair(cur.first + 1,cur.second),make_pair(cur.first - 1,cur.second) ,
				make_pair(cur.first,cur.second + 1) ,make_pair(cur.first,cur.second - 1) };
			for (auto &next : nexts)
			{
				if (next.first<0 || next.second<0 || next.first>rLen - 1 || next.second>cLen - 1) continue;
				if (!curhash[next] && matrix[next.first][next.second] <= matrix[cur.first][cur.second])
				{
					if ((hash[next] >> 0) & 1) flag |= (hash[next] >> 1);
					else Q.push(next);
					curhash[next] = 1;
				}
			}
		}
		hash[vec] |= (0x1 << 0);
		hash[vec] |= (flag << 1);
			
		return flag == 0x3;
	}
	
public:
	vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) 
	{
		vector<pair<int, int>> res;
		if (matrix.size() == 0 || matrix[0].size() == 0);
		else
		{
			rLen = matrix.size(), cLen = matrix[0].size();
			pair<int, int> vec(0, 0);
			for (vec.first = 0; vec.first < rLen; ++vec.first)
				for (vec.second = 0; vec.second < cLen; ++vec.second)
					if (bfs(matrix, vec)) res.push_back(vec);
		}
		return res;
	}
};