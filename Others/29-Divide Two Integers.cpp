class Solution
{
public:
	int divide(int dividend, int divisor)
	{
		// Check some special cases for avoiding overflow
		int left = dividend, right = divisor;
		if (right == INT_MIN) return (left == INT_MIN) ? 1 : 0;
		int quotient = 0;
		if (left == INT_MIN)
		{
			if (right == 1) return INT_MIN;
			if (right == -1) return INT_MAX;
			left += abs(right);
			quotient = 1;
		}
		left = abs(left);
		right = abs(right);
		while (left >= right)
		{
			int tmp_quotient = 1, tmp_right = right;
			while (left >= (tmp_right << 1) && (tmp_right << 1) > 0)
				tmp_right <<= 1, tmp_quotient <<= 1;
			left -= tmp_right;
			quotient += tmp_quotient;
		}
		if ((dividend ^ divisor) < 0)
			quotient = ~quotient + 1;
		return quotient;
	}
};