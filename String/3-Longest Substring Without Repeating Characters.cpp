class Solution 
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int maxlen = 0;
        std::vector<int> char2idx(128, 0);
        for (int idx = 0, left_idx = 0; idx < s.length(); ++idx)
        {
            left_idx = max(char2idx[s[idx]], left_idx);
            maxlen = max(maxlen, idx - left_idx + 1); // add 1 for boarder condition
            char2idx[s[idx]] = idx + 1;
        }
        return maxlen;
    }
};