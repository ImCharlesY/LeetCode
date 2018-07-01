class Solution
{
	int find(vector<int>& parent, int node)
	{
		if (node != parent[node])
			return parent[node] = find(parent, parent[node]);
		return parent[node];
	}
public:
	vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) 
	{
		int n = edges.size();
		vector<int> parent(n + 1, 0);
		vector<int> canA, canB;

		//step1: find node which has 2 parents
		for (auto &edge : edges)
		{
			if (parent[edge[1]] == 0)
				parent[edge[1]] = edge[0];
			else
			{
				canA = { parent[edge[1]],edge[1] };
				canB = edge;
				edge[1] = 0;	//target canB
                break;
			}
		}

		//step2: find Union
		for (int i = 1; i <= n; ++i) parent[i] = i;
		for (auto &edge : edges)
		{
			if (edge[1] == 0) continue; //skip canB, which means we remove canB from the graph
			int start = edge[0], end = edge[1], parOfstart = find(parent, start);
			if (parOfstart == end)	//still find a loop, which means we need to remove canA
			{
				if (canA.empty()) return edge;
				else return canA;
			}
			parent[end] = parOfstart;
		}

		return canB;
	}
};
