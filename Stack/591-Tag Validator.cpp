class Solution 
{
	bool CheckTagName(string forcheck, bool ending)
	{
		if (forcheck.size() < 1 || forcheck.size() > 9) return 0;
		for (auto i : forcheck) if (!isupper(i)) return 0;
		if (ending)
		{
			if (TagName.empty() || TagName.top() != forcheck) return 0;
			TagName.pop();
		}
		else
		{
			contains_tag = 1;
			TagName.push(forcheck);
		}
		return 1;
	}
	bool CheckCDATA(string forcheck)
	{
		return forcheck.find("[CDATA[") == 0;
	}
	stack<string> TagName;
	bool contains_tag;
public:
	bool isValid(string code) 
	{
		contains_tag = 0;
		if (code.size())
		{
			size_t end = code.size();
			for (size_t it = 0; it < end;)
			{
				if (TagName.empty() && contains_tag) return 0;
				switch (code[it])
				{
				case '<':
					if (!TagName.empty() && code[it + 1] == '!')
					{
						auto it2 = code.find("]]>", it + 1);
						if (it2 == string::npos || !CheckCDATA(code.substr(it + 2, it2 - it))) return 0;
						it = it2 + 2;
					}
					else
					{
						bool ending = 0;
						if (code[it + 1] == '/')
						{
							++it;
							ending = 1;
						}
						auto it2 = code.find('>', it + 1);
						if (it2 == string::npos || !CheckTagName(code.substr(it + 1, it2 - it - 1), ending)) return 0;
						it = it2;
					}
					++it;
					break;
				default:
					if (TagName.empty()) return 0;
					while (it < end && code[it] != '<') ++it;
					break;
				}
			}
		}
		return TagName.empty() && contains_tag;
	}
};