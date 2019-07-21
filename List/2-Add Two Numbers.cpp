/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution 
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
    {
        ListNode* output(new ListNode(0));
        ListNode* tail = output;

        ListNode* ptr1 = l1;
        ListNode* ptr2 = l2;
        int val = 0;
        int carry = 0;
        while (ptr1 && ptr2)
        {
            val = ptr1->val + ptr2->val + carry;
            carry = (val >= 10) ? 1 : 0;
            val = carry ? (val - 10) : val;
            tail = tail->next = new ListNode(val);
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        ListNode* ptr3 = ptr1 ? ptr1 : ptr2;
        while (ptr3)
        {
            val = ptr3->val + carry;
            carry = (val >= 10) ? 1 : 0;
            val = carry ? (val - 10) : val;
            tail = tail->next = new ListNode(val);
            ptr3 = ptr3->next;
        }
        if (carry) tail = tail->next = new ListNode(carry);
        return output->next;
    }
};