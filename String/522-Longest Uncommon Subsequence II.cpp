class Solution
{
	// function to check whether str is a subsequence of tar
	bool isSubSeq(const string& str, const string& tar)
	{
		string::const_iterator itr_i = str.begin();
		string::const_iterator itr_j = tar.begin();
		while (itr_i != str.end() && itr_j != tar.end())
		{
			if (*itr_i == *itr_j) ++itr_i;
			++itr_j;
		}
		return itr_i == str.end();
	}
public:
	// If a subsequence of string a (sub(a)) is the required longest uncommon subsequence(LUS),
	// it must be the the string a itself. Because if sub(a) is the LUS, it means that sub(a)
	// cannot be found in other strings. However, since a is an extension of sub(a) by simply
	// adding some characters, which absolutely cannot be found in other strings, thus a should
	// be the LUS. According to the above conclusion, the longer the string is, the more likely
	// the string being the LUS. Therefore, the longest string, that is not subsequence of any
	// other strings and is not identical to one of the other strings, is the LUS.
	int findLUSlength(vector<string>& strs)
	{
		// first sort the list of strings by their lengths
		sort(strs.begin(), strs.end(), [](const string& str1, const string& str2) {
			// here, we need to cluster same strings
			if (str1.length() == str2.length()) return str1 > str2;
			return str1.length() > str2.length();
			});
		vector<string>::iterator itr = strs.begin();
		// We assume that the iterator will locate at one element subsequent to target position,
		// thus if no LUS found, the iterator will locate at strs.end() + 1, which is not a valid
		// value for iterator. So we should terminate the loop manually if iterator has already
		// located at strs.end() and return -1
		while (true)
		{
			if (itr == strs.end()) return -1;
			if (itr++ >= strs.end() - 1 || *itr != *(itr - 1)) break;
			vector<string>::iterator tmp_itr = itr++;
			while (itr < strs.end() && this->isSubSeq(*itr, *tmp_itr)) ++itr;
		}
		return (itr <= strs.end()) ? (*(itr - 1)).length() : -1;
	}
};