class Solution 
{
	// Define a struct to backup board and some infomation for DFS.
	struct situation
	{
		int targetPos;
		vector<vector<char>> board;
		vector<int> board_status;
		vector<int> candidateDgt;
	};

	// This function counts how many bits are set in a bit array.
	size_t countSet(int n)
	{
		size_t c = 0;
		for (c = 0; n; ++c) n &= (n - 1);
		return c; 
	}

	// This function is used in initialization to initialize the board status.
	int getStatus(int pos, const vector<vector<char>>& board)
	{
		size_t row = pos / 9;
		size_t col = pos % 9;

		int status = 0x0FFFF;
		auto occupy = [&status](int bit) { status &= ~(8<<bit); };

		// Check the same row.
		for (size_t i = 0; i < 9; ++i) if (board[row][i] != '.') occupy(board[row][i] - '0');
		// Check the same col.
		for (size_t i = 0; i < 9; ++i) if (board[i][col] != '.') occupy(board[i][col] - '0');
		// Check the sub-boxes.
		for (size_t i = 0; i < 9; ++i) if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] != '.') occupy(board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] - '0');

		return status;
	}

	// This function changes the board status according to current step.
	void setStatus(int pos, int digit, vector<int> &board_status)
	{
		size_t row = pos / 9;
		size_t col = pos % 9;

		auto isempty = [](int status) { return status < 1 || status > 9; };
		auto occupy = [](int &status, int bit) { status &= ~(8<<bit); };

		// Check the same row.
		for (size_t i = 0; i < 9; ++i) if (isempty(board_status[row * 9 + i])) occupy(board_status[row * 9 + i], digit);
		// Check the same col.
		for (size_t i = 0; i < 9; ++i) if (isempty(board_status[i * 9 + col])) occupy(board_status[i * 9 + col], digit);
		// Check the sub-boxes.
		for (size_t i = 0; i < 9; ++i) if (isempty(board_status[(3 * (row / 3) + i / 3) * 9 + 3 * (col / 3) + i % 3])) occupy(board_status[(3 * (row / 3) + i / 3) * 9 + 3 * (col / 3) + i % 3], digit);

		board_status[pos] = digit;
	}

public:
    void solveSudoku(vector<vector<char>>& board) 
    {
        // We assign a 16-bits int as a bit array to each cell.
        // The lower 4 bits are used to store the certain digit.
        // The 4-12 bits are used to indicates the occupation
        // of the digits (1-available, 0-occupied).

        auto isempty = [](int status) { return status < 1 || status > 9; };

        // Initialization.
        vector<int> board_status(9 * 9, 0x0FFFF);
        for (size_t i = 0; i < 9; ++i)
        	for (size_t j = 0; j < 9; ++j)
        		board_status[i * 9 + j] = (board[i][j] != '.') ? (board[i][j] - '0') : getStatus(i * 9 + j, board);

        // Stack for DFS.
        stack<situation> st;

        while (1)
        {
        	bool stopFlag = 1;

        	// Search all empty cells.
	        int targetPos = -1;
	        int targetDgt = 1;
	        int minStatus = 16;
	        for (size_t i = 0; i < 9 * 9; ++i) 
	        	if (isempty(board_status[i]))
	        	{
	        		stopFlag = 0;
	        		auto count = countSet(board_status[i]);
	        		if (count < minStatus) minStatus = count, targetPos = i;
	        	}

	        if (stopFlag) return;

	        vector<int> candidateDgt;

	        // If meet a dead end. Backtracking.
	        if (minStatus == 7 || targetPos == -1) 
	        {
	        	auto backup = st.top(); st.pop();
	        	targetPos = backup.targetPos;
	        	board = backup.board;
	        	board_status = backup.board_status;
	        	candidateDgt = backup.candidateDgt;
	        }
	        else
	        	for (int i = 1; i <= 9; ++i) if ((board_status[targetPos] >> (i + 3)) & 1) candidateDgt.push_back(i);

	       	if (candidateDgt.empty())
	       		continue;
        	else if (candidateDgt.size() == 1)
        		targetDgt = candidateDgt[0];
        	else	// If there are several choices, select the last one and back up current situation.
        	{
	        	targetDgt = *(candidateDgt.end() - 1);
	        	candidateDgt.pop_back();

	        	if (!candidateDgt.empty())
	        	{
	        		situation backup;
		        	backup.targetPos = targetPos;
		        	backup.board = board;
		        	backup.board_status = board_status;
		        	backup.candidateDgt = candidateDgt;
		        	st.push(backup);
	        	}
        	}

        	setStatus(targetPos, targetDgt, board_status);
        	board[targetPos / 9][targetPos % 9] = targetDgt + '0';
        }
    }
};