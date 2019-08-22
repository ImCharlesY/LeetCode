class Solution
{
public:
	ListNode* swapPairs(ListNode* head)
	{
		if (!head || !head->next) return head;
#define RECURSIVE
#ifdef ARRAY
		vector<ListNode*> nodeAddr;
		while (head)
		{
			nodeAddr.push_back(head);
			head = head->next;
		}
		head = nodeAddr[1];
		ListNode* tail = head->next = nodeAddr[0];
		for (size_t i = 1; i < nodeAddr.size() >> 1; ++i)
		{
			tail = tail->next = nodeAddr[i << 1 | 0x1];
			tail = tail->next = nodeAddr[i << 1];
		}
		tail->next = (nodeAddr.size() & 0x1) ? *(nodeAddr.end() - 1) : nullptr;
		return head;
#endif // ARRAY

#ifdef RECURSIVE
		ListNode* temp = head->next;
		ListNode* next_head = temp->next;
		temp->next = head;
		head->next = this->swapPairs(next_head);
		return temp;
#endif // RECURSIVE
	}
};