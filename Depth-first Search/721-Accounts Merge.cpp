class Solution 
{
public:
	vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) 
	{
		/*
		Union Find:
		First, we construct two map, 'name' is a map from emails to names, 'parents' is a map from emails to their unions;
		Second, we combine all emails occurs in the same account into a union
		*/
		map<string, string> name;
		map<string, string> parents;

		function<string(string)> find = [&](string s) { return (parents[s] == s) ? s : find(parents[s]); };

		for (auto &account : accounts)
			for (size_t j = 1; j < account.size(); ++j)
			{
				parents[account[j]] = account[j];	//Set all emails' parents to be themselves
				name[account[j]] = account[0];
			}

		for (size_t i = 0; i < accounts.size(); ++i)
		{
			string p = find(accounts[i][1]);
			for (size_t j = 2; j < accounts[i].size(); ++j)
				parents[find(accounts[i][j])] = p;
		}
			
		map<string, set<string>> Union;
		for (size_t i = 0; i < accounts.size(); ++i)
			for (size_t j = 1; j < accounts[i].size(); ++j)
				Union[find(accounts[i][j])].insert(accounts[i][j]);
			
		vector<vector<string>> res;

		for (auto& p : Union)
		{
			vector<string> emails(p.second.begin(), p.second.end());
			emails.insert(emails.begin(), name[p.first]);
			res.push_back(emails);
		}

		return res;	
	}
};