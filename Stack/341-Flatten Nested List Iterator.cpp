/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class NestedIterator 
{
	stack<NestedInteger> st;
	vector<int> data;
	int index;
public:
	NestedIterator(vector<NestedInteger> &nestedList) 
	{
		for (auto &item : nestedList)
		{
			if (item.isInteger())
				data.push_back(item.getInteger());
			else
			{
				st.push(item);
				while (!st.empty())
				{
					auto tmp = st.top();
					st.pop();
					if (tmp.isInteger()) data.push_back(tmp.getInteger());
					else
						for (auto it = tmp.getList().end() - 1; it != tmp.getList().begin() - 1; --it) 
							st.push(*it);
				}
			}
		}
		index = 0;
	}

	int next() 
	{
		return data[index++];
	}

	bool hasNext()
	{
		return index < data.size();
	}
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */