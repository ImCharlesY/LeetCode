class Solution
{
	vector<string> answer;
	map<char, string> phone;
	void recusive(string catstr, const string& digits)
	{
		if (digits.empty())
		{
			this->answer.push_back(catstr);
			return;
		}
		string chs = phone[digits[0]];
		string ndigits = digits.substr(1);
		for (char ch : chs)
			this->recusive(catstr + ch, ndigits);
	}
public:
	Solution()
	{
		this->phone = map<char, string>({
			pair<char, string>('2', string("abc")), pair<char, string>('3', string("def")),
			pair<char, string>('4', string("ghi")), pair<char, string>('5', string("jkl")),
			pair<char, string>('6', string("mno")), pair<char, string>('7', string("pqrs")),
			pair<char, string>('8', string("tuv")), pair<char, string>('9', string("wxyz"))
		});
	}
	vector<string> letterCombinations(string digits)
	{
		if (!digits.empty()) this->recusive("", digits);
		return this->answer;
	}
};