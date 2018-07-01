class Solution
{
	stack<int> st;
	void operate(string token)
	{
		int right = st.top(); st.pop();
		int left = st.top(); st.pop();
		if (token == "+") st.push(left + right);
		else if (token == "-") st.push(left - right);
		else if (token == "*") st.push(left * right);
		else if (token == "/") st.push(left / right);
	}
public:
	int evalRPN(vector<string>& tokens) 
	{
		for (auto &token : tokens)
		{
			if (token == "+" || token == "-"
				|| token == "*" || token == "/") operate(token);
			else
				st.push(stoi(token));
		}
		return st.top();
	}
};