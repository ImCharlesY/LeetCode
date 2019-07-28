class Solution 
{
public: // Coud you solve it without converting the integer to a string?
    bool isPalindrome(int x) 
    {
        if (x < 0 && (x % 10 == 0 && x != 0)) return false;

        // revert half of the number
        int revertedx = 0;
        while (x > revertedx)
        {
            revertedx = revertedx * 10 + x % 10;
            x /= 10;
        }
        return (x == revertedx) || (x == revertedx/10);
    }
};