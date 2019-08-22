class Solution
{
	// Compute Partial Match Table(PMT)
	// e.g.
	// char  a b a b a b c a
	// index 0 1 2 3 4 5 6 7
	// value 0 0 1 2 3 4 0 1

	// The values in PMT is length of the longest prefix of current string
	// which is also the suffix of the string.
	// e.g., string "ababab"
	//       prefix set : a, ab, aba, abab, ababa
	//       suffix set : b, ab, bab, abab, babab
	//       thus, the longest common sub-string is "abab" and its length is 4,
	//       which is also the PMT value of string "ababab"
	vector<int> Compute_Prefix_Func(const string& P)
	{
		vector<int> pi(P.size());
		pi[0] = 0;
		int k = 0;
		for (int q = 1; q < P.size(); ++q)
		{
			while (k > 0 && P[k] != P[q]) k = pi[k - 1];
			if (P[k] == P[q]) ++k;
			pi[q] = k;
		}
		return pi;
	}

public:
	// KMP algorithm
	int strStr(string haystack, string needle)
	{
		if (needle.empty()) return 0;
		vector<int> pi = Compute_Prefix_Func(needle);
		int q = 0;
		for (int i = 0; i < haystack.size(); ++i)
		{
			while (q > 0 && needle[q] != haystack[i]) q = pi[q - 1];
			if (needle[q] == haystack[i]) ++q;
			if (q == needle.size()) return i - needle.size() + 1;
		}
		return -1;
	}
};