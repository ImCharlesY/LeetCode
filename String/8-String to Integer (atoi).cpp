class Solution 
{
    bool isdigit(char ch)
    {
        return ch >= '0' && ch <= '9';
    }
public:
    int myAtoi(string str) 
    {
        int res = 0;
        int sign = 0; // 0 - yet; 1 - positive; 2 - negative.
        for (size_t i = 0; i < str.length(); ++i)
        {
            if (str[i] == ' ')
            {
                if (sign == 0) continue;
                else break;
            }
            else if (str[i] == '+' || str[i] == '-')
            {
                if (sign == 0) sign = (str[i] == '+') ? 1 : 2;
                else break;
            }
            else if (isdigit(str[i]))
            {
                if (sign == 0) sign = 1;
                int residual = (str[i] - '0');
                residual = sign == 2 ? -residual : residual;
                if (res > INT_MAX/10 || (res == INT_MAX/10 && residual > 7)) return INT_MAX;
                if (res < INT_MIN/10 || (res == INT_MIN/10 && residual < -8)) return INT_MIN;
                res = res * 10 + residual;
            }
            else break;
        }
        return res;
    }
};