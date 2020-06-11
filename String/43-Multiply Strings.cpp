/* 43. Multiply Strings
Category: Medium
Problem Description:
    Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2, also represented as a string.
    Example 1:
        Input: num1 = "2", num2 = "3"
        Output: "6"
    Example 2:
        Input: num1 = "123", num2 = "456"
        Output: "56088"
    Note:
        The length of both num1 and num2 is < 110.
        Both num1 and num2 contain only digits 0-9.
        Both num1 and num2 do not contain any leading zero, except the number 0 itself.
        You must not use any built-in BigInteger library or convert the inputs to integer directly.
*/
class Solution
{
public:
    // Just a simple big integer problem.
    string multiply(string num1, string num2)
    {
        if (num1 == "0" || num2 == "0") return string("0");
        if (num1.size() < num2.size()) return this->multiply(num2, num1);
        vector<short> elt_product(num1.size() + num2.size() - 1, 0);
        for (short i = num1.size() - 1; i >= 0; --i)
            for (short j = num2.size() - 1; j >= 0; --j)
                elt_product[i + j] += ((num1[i] - '0') * (num2[j] - '0'));
        short carry = 0;
        string product(elt_product.size(), '0');
        for (short i = product.size() - 1; i >= 0; --i)
        {
            short temp = elt_product[i] + carry;
            product[i] = '0' + (temp % 10);
            carry = temp / 10;
        }
        if (carry) product.insert(product.begin(), '0' + carry);
        return product;
    }
};