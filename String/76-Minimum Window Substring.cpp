class Solution 
{
public:
    string minWindow(string s, string t) 
    {
    	if (s.size() == 0 || t.size() == 0)
    		return string("");

        size_t ptr_left = 0, ptr_right = 0;

        // construct a dictionary to keep a count of all the unique characters in string t
        unordered_map<char, size_t> dictT;
        for (size_t i = 0; i < t.size(); ++i)
        	++dictT[t[i]];

        // number of unique characters in t
        size_t required_num = dictT.size();
        // number of matched characters in s
        size_t matched_num = 0;

        // dictionary to keep a count of all the unique characters in the current window
        unordered_map<char, size_t> winsCnt;

        // window length, ptr_left
        vector<size_t> ans_tuple({INT_MAX, 0});

        while (ptr_right < s.size())
        {
        	// extend window by adding right point
        	++winsCnt[s[ptr_right]];

        	// if the frequency of the current character in current window meets
        	// the desired count in t, then increment the matched count by 1
        	if (winsCnt[s[ptr_right]] == dictT[s[ptr_right]])
        		++matched_num;

        	// contract window by adding left point
        	while (ptr_left <= ptr_right && matched_num == required_num)
        	{
        		if (ans_tuple[0] == INT_MAX || ptr_right - ptr_left + 1 < ans_tuple[0])
        		{
        			ans_tuple[0] = ptr_right - ptr_left + 1;
        			ans_tuple[1] = ptr_left;
        		}
        		--winsCnt[s[ptr_left]];
        		if (winsCnt[s[ptr_left]] < dictT[s[ptr_left]])
        			--matched_num;
        		++ptr_left;
        	}
        	++ptr_right;
        }

        return ans_tuple[0] == INT_MAX ? string("") : s.substr(ans_tuple[1], ans_tuple[0]);
    }
};