class Solution 
{
public:
    /*Just find out the regular pattern.
    Period = numRows -1
    Offset = Index % Period
    -------------------------------
    | Index Offset |    Stride    |
    -------------------------------
    |      0       | 2(Period -1) |
    |      1       | 2(Period -2) |
    |     ...      |     ...      |
    |  Period - 1  |      2       |
    -------------------------------
    */
    string convert(string s, int numRows) 
    {
        if (numRows <= 1) return s;
        string res;
        for (int idx = 0; idx < numRows; ++idx)
        {
            for (int j = idx; j < s.length(); )
            {
                res += s[j];
                j += 2 * (numRows - (j % (numRows - 1) + 1));
            }
        }
        return res;
    }
};