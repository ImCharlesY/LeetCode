class Solution 
{
public:
    int maxArea(vector<int>& height)
    {
        // Two-pointer method:
        // Motivation: The area formed between bars is limited by the height
        //             of the shorter one.
        // Using two pointers, one at the beginning and one at the end. Shrink
        // the distance of two pointers to iterate over the array to get the
        // maximum area. Every time we move the pointer at the shorter bar inwards.
        // Because the area is limited by the shorter bar, if we try to move the 
        // pointer at the longer bar, we won't gain any bonus. Although moving the
        // shorter bar's pointer will cause reduction in the width, it is probably
        // that a relatively longer bar obtained by moving the shorter bar's pointer
        // might overcome the reduction of area.
        int area = 0;
        int ptrL = 0, ptrR = height.size() - 1;
        while (ptrL < ptrR)
        {
            area = max(area, (ptrR - ptrL) * min(height[ptrL], height[ptrR]));
            if (height[ptrL] < height[ptrR]) ++ptrL;
            else --ptrR;
        }
        return area;
    }
};