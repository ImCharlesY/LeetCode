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
    ListNode* _reverseKGroup(ListNode*& head, int k) 
    {
        if (k == 1) return head;
        ListNode* tail = head;
        for (int i = 0; i < k - 1 && tail; ++i) tail = tail->next;
		if (!tail) return head;
        
        _reverseKGroup(tail->next, k);

		ListNode* nextGroup = tail->next;
		ListNode* pre = new ListNode(0);
		ListNode* cur = head;
		ListNode* next = cur->next;

		while (cur != tail)
		{
			cur->next = pre;
			pre = cur;
			cur = next;
			next = cur->next;
		}
		cur->next = pre;
		head->next = nextGroup;
		head = tail;

		return head;
    }
public:
	ListNode* reverseKGroup(ListNode* head, int k) 
    {
    	return _reverseKGroup(head, k);
    }
};