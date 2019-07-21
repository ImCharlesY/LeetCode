/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class ListNodeComp
{
public:
    bool operator()(const ListNode* a, const ListNode* b) const
    {
        return a->val > b->val;
    }
};

class Solution 
{
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) 
    {
        std::priority_queue<ListNode*, vector<ListNode*>, ListNodeComp> pq;
        ListNode* mergedList(new ListNode(0));
        ListNode* tail = mergedList;

        // Construct a minimum heap.
        if (l1) pq.push(l1);
        if (l2) pq.push(l2);

        while (!pq.empty())
        {
            auto cur = pq.top();
            pq.pop();

            tail = tail->next = new ListNode(cur->val);

            if (cur->next) pq.push(cur->next);
        }

        return mergedList->next;
    }
};