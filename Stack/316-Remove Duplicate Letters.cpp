class Solution 
{
public:
	string removeDuplicateLetters(string s) 
	{
		string res = "";
		map<char, bool> hash;
		map<char, int> cnt;
		for (auto i : s) ++cnt[i];
		for (auto i : s)
		{
			while (res.size() && res.back() > i && !hash[i] && cnt[res.back()] > 1)
			{
				hash[res.back()] = 0;
				--cnt[res.back()];
				res.pop_back();
			}
			if (!hash[i])
			{
				res.push_back(i);
				hash[i] = 1;
			}
			else --cnt[i];
		}
		return res;
	}
};