class Solution 
{
	string shrink(string s)
	{
		while (s.size())
		{
			int start = 0;
			int done = 1;
			for (int i = 0; i <= s.size(); ++i)
				if (i == s.size() || s[i] != s[start])
				{
					if (i - start >= 3)
					{
						s = s.substr(0, start) + s.substr(i);
						done = 0;
						break;
					}
					start = i;
				}
			if (done) break;
		}
		return s;
	}
	int priFind(string b, string h)
	{
		if (b.empty()) return 0;
		if (h.empty()) return 6;
		int res = 6;
		for (int i = 0; i < h.size(); ++i)
		{
			int j = 0, n = b.size();
			while (j < n)
			{
				int k = b.find(h[i], j);
				if (k == string::npos) break;
				if (k < n - 1 && b[k] == b[k + 1])
				{
					string nextb = shrink(b.substr(0, k) + b.substr(k + 2));
					if (nextb.empty()) return 1;
					string nexth = h;
					nexth.erase(i, 1);
					res = min(res, priFind(nextb, nexth) + 1);
					++k;
				}
				else if (i > 0 && h[i] == h[i - 1])
				{
					string nextb = shrink(b.substr(0, k) + b.substr(k + 1));
					if (nextb.empty()) return 2;
					string nexth = h;
					nexth.erase(i - 1, 2);
					res = min(res, priFind(nextb, nexth) + 2);
				}
				j = k + 1;
			}
		}
		return res;
	}
public:
	int findMinStep(string board, string hand)
	{
		sort(hand.begin(), hand.end());
		int res = priFind(board, hand);
		return res > hand.size() ? -1 : res;
	}
};