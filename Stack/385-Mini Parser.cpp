/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution 
{
	//stack<string> st;
	stack<NestedInteger> stk;
	/*bool mygetline(stringstream &Str, string &InOneItem)
	{
		int cnt = 0;
		char cur;
		InOneItem.clear();
		while (Str.get(cur))
		{
			if (cur == '[') ++cnt;
			else if (cur == ']') --cnt;
			if (cur == ',' && cnt == 0) break;
			InOneItem += cur;
		}
		return (Str) ? 1 : 0;
	}*/
public:
	NestedInteger deserialize(string s) 
	{
		/*
		st.push(s);
		stk.push(NestedInteger());
		while (!st.empty())
		{
			string OneItem = st.top();
			st.pop();
			if (OneItem[0] != '[') stk.top().add(NestedInteger(stoi(OneItem)));
			else
			{
				OneItem = OneItem.substr(1, OneItem.size() - 2);
				stringstream Str(OneItem);
				string InOneItem;
				stk.push(NestedInteger());
				stack<string> tmp;
				while (mygetline(Str, InOneItem)) tmp.push(InOneItem);
				if (InOneItem.size() != 0) tmp.push(InOneItem);
				while (!tmp.empty())
				{
					st.push(tmp.top());
					tmp.pop();
				}
				auto ni = stk.top();
				stk.pop();
				stk.top().add(ni);
			}
		}
		return stk.top().getList().front();
		*/
		function<bool(char)> isnumber = [](char c) { return (c == '-') || isdigit(c); };
		
		stk.push(NestedInteger());

		for (auto it = s.begin(); it != s.end();) 
		{
			const char & c = (*it);
			if (isnumber(c)) 
			{
				auto it2 = find_if_not(it, s.end(), isnumber);
				int val = stoi(string(it, it2));
				stk.top().add(NestedInteger(val));
				it = it2;
			}
			else 
			{
				if (c == '[') stk.push(NestedInteger());
				else if (c == ']') 
				{
					auto ni = stk.top();
					stk.pop();
					stk.top().add(ni);
				}
				++it;
			}
		}
		return stk.top().getList().front();
	}
};