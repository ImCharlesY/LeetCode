class Solution
{
	vector<string> ans;
	void recursive(int num_left, int num_right, string curstr)
	{
		// if (num_left == 0 && num_right == 0) 
		// 	ans.push_back(curstr);
		// if (num_left > 0)
		// 	this->recursive(num_left - 1, num_right, curstr + '(');
		// if (num_right > 0 && num_left < num_right)
		// 	this->recursive(num_left, num_right - 1, curstr + ')');

		// We can speed up the algorithm by reducing the depth of recursive
		if (num_left == 0)
		{
			for (size_t i = 0; i < num_right; ++i)
				curstr += ')';
			ans.push_back(curstr);
			return;
		}
		this->recursive(num_left - 1, num_right, curstr + '(');
		if (num_right > num_left) // this condition inplies num_right > 0
			this->recursive(num_left, num_right - 1, curstr + ')');
	}
public:
	vector<string> generateParenthesis(int n)
	{
#define RECURSIVE
#ifdef RECURSIVE
		this->recursive(n, n, "");
		return this->ans;
#endif // RECURSIVE

#ifdef DP
		// Decomposite the problem into small sub-problems
		// Consider the simplest case where n = 0: f(0) = ""
		// Then when n = 1: f(1) = "()" = "("f(0)")"
		// Then n = 2: f(2) = "()()", "(())" = "("f(0)")"f(1), "("f(1)")"
		// Then n = 3: f(3) = "("f(0)")"f(2), "("f(1)")"f(1), "("f(2)")"
		// Thus, the result of f(n) will be put an extra () pair to f(n-1),
		// and there will be i pairs () inside the extra () and n - 1 - i 
		// pairs () outside the extra pair
		unordered_map<int, vector<string>> f;
		f[0].push_back("");
		for (size_t i = 1; i <= n; ++i)
			for (size_t j = 0; j < i; ++j)
				for (string& in : f[j])
					for (string& out : f[i - 1 - j])
						f[i].push_back("(" + in + ")" + out);
		return f[n];
#endif // DP
	}
};