class Solution 
{
public:
    int romanToInt(string s) 
    {
        int res = 0;
        for (size_t i = 0; i < s.length(); ++i)
        {
            char next = (i < s.length() - 1) ? s[i + 1] : 'I';
            bool skip = false;
            switch (s[i])
            {
            case 'I':
                if (next == 'V') res += 4, skip = true;
                else if (next == 'X') res += 9, skip = true;
                else res += 1;
            break;
            case 'V':
                res += 5;
            break;
            case 'X':
                if (next == 'L') res += 40, skip = true;
                else if (next == 'C') res += 90, skip = true;
                else res += 10;
            break;
            case 'L':
                res += 50;
            break;
            case 'C':
                if (next == 'D') res += 400, skip = true;
                else if (next == 'M') res += 900, skip = true;
                else res += 100;
            break;
            case 'D':
                res += 500;
            break;
            case 'M':
                res += 1000;
            break;
            default: break;
            }
            if (skip) ++i;
        }
        return res;
    }
};