class Solution
{
public:
	// do this in one pass
	ListNode* removeNthFromEnd(ListNode* head, int n)
	{
		ListNode* tail = head;
		ListNode* target = head;
		ListNode* pre_target = nullptr;
		int len = 0;
		if (head)
		{
			while (tail)
			{
				tail = tail->next;
				++len;
				if (len > n)
				{
					pre_target = target;
					target = target->next;
				}
			}
			if (pre_target)
				pre_target->next = target->next;
			else
				head = target->next;
			delete target;
		}
		return head;
	}
};