class Solution 
{
public:
    vector<int> findSubstring(string s, vector<string>& words) 
    {
        // define a vector to return result
        vector<int> indexes;

        if (words.empty()) return indexes;

        // counts every word
        unordered_map<string, int> counts;
        for (auto word : words) ++counts[word];
        
        // get the length of string, number of words and the length of each word
        int str_len = s.length(), words_num = words.size(), words_len = words[0].length();

        // because of the length of matched substring is words_num * words_len, 
        // we only need to traverse the string from index 0 to str_len - words_num * words_len + 1
        for (int i = 0; i < str_len - words_num * words_len + 1; ++i) 
        {
            // define a vector to record the time of each word we use in substring
            unordered_map<string, int> visited;
            int j = 0;
            for (; j < words_num; ++j) 
            {
                string word = s.substr(i + j * words_len, words_len);
                if (counts.find(word) != counts.end())
                {
                    ++visited[word];
                    if (visited[word] > counts[word]) break;
                }
                else break;
            }
            if (j == words_num) indexes.push_back(i);
        }
        return indexes;
    }
};