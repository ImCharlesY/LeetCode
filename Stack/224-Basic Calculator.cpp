class Solution 
{
	enum Token { EOL, VALUE, OPAREN, CPAREN, PLUS, MINUS };
	stack<int> PostFixStack;
	stack<Token> OpStack;
	std::istringstream Str;			//输入字符流

	int CurrentValue;			//当前操作数数值
	Token LastToken;				//刚读入的各种符号，被区分为：EOL, VALUE, OPAREN, CPAREN, PLUS, MINUS等6种
	Token GetToken()				//读入符号，记录在LastToken里
	{
		char Ch;
		while (Str.get(Ch) && Ch == ' ');				//若为空格，则读取下一个字符（也即跳过空格）
		if (Str.good() && Ch != '\n' && Ch != '\0')
		{
			switch (Ch)
			{
			case '(':return OPAREN;
			case ')':return CPAREN;
			case '+':return PLUS;
			case '-':return MINUS;
			default:Str.putback(Ch);					//其他字符可能是操作数字符，所以将其写回
				Str >> CurrentValue;		//得到的操作数写进CurrentValue
				return VALUE;
			}
		}
		return EOL;
	}
	void BinaryOp(Token TopOp)			//完成运算符的相应的运算
	{
		int R = PostFixStack.top(); PostFixStack.pop();
		int L = PostFixStack.top(); PostFixStack.pop();
		if (TopOp == PLUS) PostFixStack.push(L + R);
		else if (TopOp == MINUS) PostFixStack.push(L - R);
		OpStack.pop();
	}
	void ProcessToken()			//处理各种符号以及如何进行计算的函数
	{
		Token TopOp;
		switch (LastToken)
		{
		case VALUE:PostFixStack.push(CurrentValue); return;
		case CPAREN:													//开闭括号之间的所有运算可以进行
			while ((TopOp = OpStack.top()) != OPAREN && TopOp != EOL) BinaryOp(TopOp);
			OpStack.pop();							//清除开括号
			break;
		default:
			while (!OpStack.empty() && OpStack.top() != OPAREN && LastToken != OPAREN)
			{
				TopOp = OpStack.top();
				BinaryOp(TopOp);
			}
			if (LastToken != EOL) OpStack.push(LastToken);
		}
	}
public:
	int calculate(string s) 
	{
		Str = istringstream(s);
		do
		{
			LastToken = GetToken();
			ProcessToken();
		} while (LastToken != EOL);				//当未得到行结束标志时，继续运算
		
		return PostFixStack.top();
	}
};