class Solution 
{
	struct func
	{
		int id;
		int starttime;
		bool broken;
		func(int i, int t, bool b = 0) :id(i), starttime(t), broken(b) {}
	};
	stack<func> st;
	int id, curtime;
	string command;
public:
	vector<int> exclusiveTime(int n, vector<string>& logs) 
	{
		vector<int> res(n);
		for (auto &log : logs)
		{
			stringstream Str(log);
			getline(Str, command, ':');
			id = stoi(command);
			getline(Str, command, ':');
			Str >> curtime;
			if (command == "start")
			{
				if (!st.empty())
				{
					st.top().broken = 1;
					res[st.top().id] += curtime - st.top().starttime;
					st.top().starttime = curtime;
				}
				st.push(func(id, curtime));
			}
			else
			{
				auto fun = st.top();
				st.pop();
				res[id] += curtime - fun.starttime + 1;
				if (!st.empty() && st.top().broken)
				{
					st.top().broken = 0;
					st.top().starttime = curtime + 1;
				}
			}
		}
		return res;
	}
};