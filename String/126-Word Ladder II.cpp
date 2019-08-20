#define SOLUTION3
class Solution
{
	vector<vector<string>> ans;
	deque<string> OnePath;                           // deque for recording path in backtracking
	unordered_map<string, pair<int, vector<string>>> visited;  
	                                                 // record whether a string (vertex) has been visited,
													 // also how far it from beginWord, and its antecedent
													 // vertices in paths

	// Backtracking to construct paths from visited linked list
	void GetAns(const string& cur, const string& bW)
	{
		OnePath.push_front(cur);
		if (cur == bW)
			ans.push_back(vector<string>(OnePath.begin(), OnePath.end()));
		else
			for (auto& pre : visited[cur].second)
				GetAns(pre, bW);
		OnePath.pop_front();
	}

public:
	// Key idea: Build a graph where strings are vertices and arcs are added into if two strings can transfrom to each other
	// within one step. Then we can apply BFS to search all transformation paths.
#ifdef SOLUTION1
	vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList)
	{
		// If the endWord is not in wordList, therefore no possible transformation
		if (find(wordList.begin(), wordList.end(), endWord) == wordList.end()) return ans;

		// ===== Build graph by constructing adjacency list
		if (find(wordList.begin(), wordList.end(), beginWord) == wordList.end())
			wordList.push_back(beginWord);
		int n = wordList.size(), len = beginWord.size();
		map<string, vector<string>> AdjList;
		for (size_t i = 0; i < n; ++i)
			for (size_t j = i + 1; j < n; ++j)
			{
				// Calculate distance between two strings
				int cnt = 0;
				for (size_t k = 0; k < len; ++k)
					cnt += (wordList[i][k] == wordList[j][k]) ? 1 : 0;
				if (cnt == len - 1)
				{
					AdjList[wordList[i]].push_back(wordList[j]);
					AdjList[wordList[j]].push_back(wordList[i]);
				}
			}

		// ===== The procedure of BFS
		// Queue for BFS where queue elementsa are type of pair -- (current vertex to search, previous vertex)
		// the previous vertex is recorded for avoiding loopback
		queue<pair<string, string>> Q;
		visited[beginWord].first = 0;
		Q.push(pair<string, string>(beginWord, beginWord));
		while (!Q.empty())
		{
			auto top = Q.front(); Q.pop();
			auto cur = top.first;
			auto pre = top.second;
			if (cur == endWord) continue;
			for (auto& item : AdjList[cur])
			{
				if (item == pre) continue; // avoid loopback
				// if `item` is not visited yet, initialize it
				if (visited[item].first == 0) visited[item].first = INT_MAX;
				if (visited[cur].first + 1 <= visited[item].first)
				{
					if (visited[cur].first + 1 < visited[item].first)
					{
						visited[item].second.clear();
						visited[item].first = visited[cur].first + 1;
						Q.push(pair<string, string>(item, cur));
					}
					visited[item].second.push_back(cur);
				}
			}
		}

		// ===== Construct the paths
		GetAns(endWord, beginWord);

		return ans;
	}
#endif // SOLUTION1

#ifdef SOLUTION2
	vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList)
	{
		// If the endWord is not in wordList, therefore no possible transformation
		if (find(wordList.begin(), wordList.end(), endWord) == wordList.end()) return ans;

		// ===== Build graph by constructing adjacency list
		if (find(wordList.begin(), wordList.end(), beginWord) == wordList.end())
			wordList.push_back(beginWord);
		int n = wordList.size(), len = beginWord.size();
		// Traverse through string positions and alphabet table instead of wordList to match strings
		// n - length of wordList; m - length of string
		// In Solution 1:
		//    1. Traverse through wordList : O(n)
		//    2. Traverse through wordList again : O(n)
		//    3. Traverse through string positions : O(m)
		//    *. Total time complexity : O(mn^2)
		// Here:
		//    1. Traverse through wordList : O(n)
		//    2. Traverse through alphabet table : O(26) = O(1)
		//    3. Traverse through string positions : O(m)
		//    4. Search transformed string : 
		//       a. wordList (vector) : O(n)
		//       b. wordDict (set) : O(logn)
		//    *. Total time complexity : O(mn^2) (vector) or O(mnlogn) (set)
		unordered_set<string> wordDict;
		for (string& w : wordList)
			wordDict.insert(w);
		unordered_map<string, vector<string>> AdjList;
		for (size_t i = 0; i < n; ++i)
			for (char ch = 'a'; ch <= 'z'; ++ch)
				for (size_t j = 0; j < len; ++j)
				{
					if (wordList[i][j] == ch) continue;
					string change = wordList[i];
					change[j] = ch;
					if (wordDict.count(change))
						AdjList[wordList[i]].push_back(change);
				}

		// ===== The procedure of BFS
		// Queue for BFS where queue elementsa are type of pair -- (current vertex to search, previous vertex)
		// the previous vertex is recorded for avoiding loopback
		queue<pair<string, string>> Q;
		visited[beginWord].first = 0;
		Q.push(pair<string, string>(beginWord, beginWord));
		while (!Q.empty())
		{
			auto top = Q.front(); Q.pop();
			auto cur = top.first;
			auto pre = top.second;
			if (cur == endWord) continue;
			for (auto& item : AdjList[cur])
			{
				if (item == pre) continue; // avoid loopback
				// if `item` is not visited yet, initialize it
				if (visited[item].first == 0) visited[item].first = INT_MAX;
				if (visited[cur].first + 1 <= visited[item].first)
				{
					if (visited[cur].first + 1 < visited[item].first)
					{
						visited[item].second.clear();
						visited[item].first = visited[cur].first + 1;
						Q.push(pair<string, string>(item, cur));
					}
					visited[item].second.push_back(cur);
				}
			}
		}

		// ===== Construct the paths
		GetAns(endWord, beginWord);

		return ans;
}
#endif // SOLUTION2

#ifdef SOLUTION3
	vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList)
	{
		// If the endWord is not in wordList, therefore no possible transformation
		if (find(wordList.begin(), wordList.end(), endWord) == wordList.end()) return ans;


		// ===== Build graph by constructing adjacency list
		if (find(wordList.begin(), wordList.end(), beginWord) == wordList.end())
			wordList.push_back(beginWord);
		int n = wordList.size(), len = beginWord.size();
		unordered_set<string> wordDict;
		for (string& w : wordList)
			wordDict.insert(w);
		unordered_map<string, vector<string>> AdjList;
		unordered_map<string, bool> AdjListExist;

		// ===== The procedure of BFS
		// Queue for BFS where queue elementsa are type of pair -- (current vertex to search, previous vertex)
		// the previous vertex is recorded for avoiding loopback
		queue<pair<string, string>> Q;
		visited[beginWord].first = 0;
		Q.push(pair<string, string>(beginWord, beginWord));
		while (!Q.empty())
		{
			auto top = Q.front(); Q.pop();
			auto cur = top.first;
			auto pre = top.second;
			if (cur == endWord) continue;
			// Build graph that only considers `valid` vertices
			if (!AdjListExist[cur])
			{
				for (char ch = 'a'; ch <= 'z'; ++ch)
					for (size_t i = 0; i < len; ++i)
					{
						if (cur[i] == ch) continue;
						string change = cur;
						change[i] = ch;
						if (wordDict.count(change))
							AdjList[cur].push_back(change);
					}
				AdjListExist[cur] = true;
			}
			for (auto& item : AdjList[cur])
			{
				if (item == pre) continue; // avoid loopback
				// if `item` is not visited yet, initialize it
				if (visited[item].first == 0) visited[item].first = INT_MAX;
				if (visited[cur].first + 1 <= visited[item].first)
				{
					if (visited[cur].first + 1 < visited[item].first)
					{
						visited[item].second.clear();
						visited[item].first = visited[cur].first + 1;
						Q.push(pair<string, string>(item, cur));
					}
					visited[item].second.push_back(cur);
				}
			}
		}

		// ===== Construct the paths
		GetAns(endWord, beginWord);

		return ans;
	}
#endif // SOLUTION3
};