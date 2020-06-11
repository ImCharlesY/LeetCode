/* 44. Wildcard Matching
Category: Hare
Problem Description:
    Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*'.
    '?' Matches any single character.
    '*' Matches any sequence of characters (including the empty sequence).
    The matching should cover the entire input string (not partial).
    Note:
        s could be empty and contains only lowercase letters a-z.
        p could be empty and contains only lowercase letters a-z, and characters like ? or *.
    Example 1:
        Input:
            s = "aa"
            p = "a"
        Output: false
        Explanation: "a" does not match the entire string "aa".
    Example 2:
        Input:
            s = "aa"
            p = "*"
        Output: true
        Explanation: '*' matches any sequence.
    Example 3:
        Input:
            s = "cb"
            p = "?a"
        Output: false
        Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
    Example 4:
        Input:
            s = "adceb"
            p = "*a*b"
        Output: true
        Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
    Example 5:
        Input:
            s = "acdcb"
            p = "a*c?b"
        Output: false
*/
class Solution 
{
    // Recursive Solution:
    // This problem can be decomposited into sub-problems in a recursive manner. For current stage of
    // the sub-problem, we only consider whether the first characters of string and pattern match or not.
    // If not, then the whole pattern fails to match the string, or we could turn to the rest of the string
    // and pattern. The above idea can easily leads to the recursive solution:
    //   switch (p[0])
    //     case '*': turn to ||{isMatch(s[k:], p[1:]), k \in [0, len(s) - 1]};
    //     case '?': turn to isMatch(s[1:], p[1:]);
    //     case 'a-z': 1. if s[0] == p[0], turn to isMatch(s[1:], p[1:]);
    //                 2. if s[0] != p[0], return false.
    //
    // Dynamic Programming Solution:
    // The above recursive solution solves the problem from left to right, which introduces a lot of redundant
    // computation. Therefore, dynamic programming could be employed to save these redundant computation. Inspired
    // by the recursive solution, we can define the state and state transition equation as:
    //     state: d[i, j] = isMatch(s[i:], p[j:]);
    //     state transition equation: d[i, j] = d[i+1, j+1],             if s[i] == p[j] or p[j] == '?';
    //                                          d[i, j+1] | d[i+1, j],   if p[j] == '*';
    //                                          0,                       otherwise.
    // 
    // Advanced Solution -- Linear Scan with Backtracking:
    // In fact, we can observe that the main difference between this problem and string matching (P28) is that
    // there exists '*' in this problem which can match any sequence of characters. Without '*', we can solve
    // string matching by using two pointers to check pair of characters from string and pattern one by one.
    // However, when there are several '*' in pattern, the action of the pointer for string has several choices:
    // stay for matching empty sequence, move forward 1 character for matching sequence of 1 character, and so on.
    // 
public:
    bool isMatch_Recursion_ver(const string &s, const string &p) 
    {
        if (p.empty()) return s.empty();
        
        // If the first character is not a star, we match the first character and 
        // let both text and pattern move on one step.
        if (p[0] != '*')
        {
            bool preMatch = (!s.empty()) && (p[0] == '?' || s[0] == p[0]);
            return preMatch && isMatch_Recursion_ver(s.substr(1), p.substr(1));
        }
        // If a star is present in the pattern, we may delete a matched sequence in 
        // text and check if the rest of the text matches the pattern. 
        else
        {
            bool judge = 0;
            for (size_t i = 0; i <= s.size(); ++i)
                judge = judge || isMatch_Recursion_ver(s.substr(i), p.substr(1));
            return judge;
        }

    }

    bool isMatch_DP_ver(const string &s, const string &p)
    {
        // We just use an array to store results of the calls isMatch(s[i:], p[j:]).
        // dp[i][j] means the matching result of isMatch(s[i:], p[j:]).
        vector<vector<bool>> dp(s.size() + 1, vector<bool>(p.size() + 1, 0));

        // The following for loop initialize the dp array.
        // In this case, both text and pattern are empty.
        dp[s.size()][p.size()] = 1;             
        // The follows initialize first row.
        for (int j = p.size() - 1; j >= 0; --j)
            if (p[j] == '*') dp[s.size()][j] = 1;
            else break;

        // Recursion
        for (int i = s.size() - 1; i >= 0; --i)
            for (int j = p.size() - 1; j >= 0; --j)
            {
                // If the first character is not a star, we match the first character and 
                // let both text and pattern move on one step.
                if (p[j] == '?' || s[i] == p[j])
                    dp[i][j] = dp[i + 1][j + 1];
                // If the first character is a star, there are 2 matched cases:
                // first, dp[i+1][j] means that * acts like any sequences;
                // second, dp[i][j+1] means that * acts like an empty sequence.
                else if (p[j] == '*')
                    dp[i][j] = dp[i + 1][j] || dp[i][j + 1];
                else
                    dp[i][j] = 0;
            }

        return dp[0][0];
    }

    bool isMatch_BackTrack_ver(const string &s, const string &p)
    {
        int sLen = s.size(), pLen = p.size();
        int sIdx = 0, pIdx = 0;
        int sBIdx = -1, pBIdx = -1;
        while (sIdx < sLen)
        {
            // if pattern character == string character or pattern character == '?'.
            if (pIdx < pLen && (p[pIdx] == '?' || p[pIdx] == s[sIdx]))
            {
                ++pIdx;
                ++sIdx;
            }
            // if pattern character == '*', save checkpoints.
            else if (pIdx < pLen && p[pIdx] == '*')
            {
                sBIdx = sIdx;
                pBIdx = pIdx;
                ++pIdx;     // when first meet, assume '*' matches empty sequence.
            }
            // if pattern character != string character or pattern is used up,
            // check whether there exists checkpoints.
            else
            {
                // if pattern contains no '*'.
                if (sBIdx == -1) return false;
                else
                {   // backtracking: sIdx moves to one character after last checkpoint,
                    // so the last '*' now matches sequence of 1/2/3/... characters.
                    pIdx = pBIdx + 1;
                    sIdx = sBIdx + 1;
                    sBIdx = sIdx;      // update backtracking checkpoint.
                }
            }
        }
        // if there remains characters in pattern, they should all be '*'.
        for (; pIdx < pLen; ++pIdx) if (p[pIdx] != '*') return false;
        return true;
    }

    bool isMatch(string s, string p)
    {
        return isMatch_BackTrack_ver(s, p);
    }
};