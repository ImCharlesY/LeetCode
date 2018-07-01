class MyStack 
{
	std::queue<int> q1;
	std::queue<int> q2;
public:
	/** Initialize your data structure here. */
	MyStack() 
	{

	}

	/** Push element x onto stack. */
	void push(int x) 
	{
		if (!q2.empty()) q2.push(x);
		else q1.push(x);
	}

	/** Removes the element on top of the stack and returns that element. */
	int pop() 
	{
		std::queue<int> *pq1, *pq2;
		if (!q1.empty()) pq1 = &q1, pq2 = &q2;
		else pq1 = &q2, pq2 = &q1;
		while ((*pq1).size() > 1)
		{
			(*pq2).push((*pq1).front());
			(*pq1).pop();
		}
		int tmp = (*pq1).front();
		(*pq1).pop();
		return tmp;
	}

	/** Get the top element. */
	int top() 
	{
		std::queue<int> *pq1, *pq2;
		if (!q1.empty()) pq1 = &q1, pq2 = &q2;
		else pq1 = &q2, pq2 = &q1;
		while ((*pq1).size() > 1)
		{
			(*pq2).push((*pq1).front());
			(*pq1).pop();
		}
		int tmp = (*pq1).front();
		(*pq2).push((*pq1).front());
		(*pq1).pop();
		return tmp;
	}

	/** Returns whether the stack is empty. */
	bool empty() 
	{
		return q1.empty() && q2.empty();
	}
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack obj = new MyStack();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.top();
 * bool param_4 = obj.empty();
 */