/* 36. Valid Sudoku
Category: Medium
Problem Description:
    Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:
    Each row must contain the digits 1-9 without repetition.
    Each column must contain the digits 1-9 without repetition.
    Each of the 9 3x3 sub-boxes of the grid must contain the digits 1-9 without repetition.
    A partially filled sudoku which is valid.
    The Sudoku board could be partially filled, where empty cells are filled with the character '.'.
    Note:
        A Sudoku board (partially filled) could be valid but is not necessarily solvable.
        Only the filled cells need to be validated according to the mentioned rules.
        The given board contain only digits 1-9 and the character '.'.
        The given board size is always 9x9.
*/
class Solution
{
    bool updateRecord(vector<bitset<9>>& occupied, const bitset<9>& bitmask, size_t index)
    {
        auto bitmodified = occupied[index] | bitmask;
        if (bitmodified == occupied[index])
            return false;
        occupied[index] = bitmodified;
        return true;
    }
public:
    // According to the problem description, only the filled cells need to be validated.
    // Therefore, we need in total 27 bitsets (9 for rows, 9 for cols and 9 for boxes) to
    // for recording.
#ifdef V1
    bool isValidSudoku(vector<vector<char>>& board)
    {
        vector<bitset<9>> occupied(27, bitset<9>(0));
        for (size_t row = 0; row < 9; ++row)
            for (size_t col = 0; col < 9; ++col)
            {
                if (board[row][col] == '.') continue;
                auto bitmask = bitset<9>().set(board[row][col] - '0' - 1);
                bitset<9> bitmodified;
                if (!this->updateRecord(occupied, bitmask, row))
                    return false;
                if (!this->updateRecord(occupied, bitmask, col + 9))
                    return false;
                if (!this->updateRecord(occupied, bitmask, 3 * (row / 3) + (col / 3) + 18))
                    return false;
            }
        return true;
    }
#endif //V1
#ifdef V2
    bool isValidSudoku(vector<vector<char>>& board)
    {
        vector<int> occupied_row(9, 0);
        vector<int> occupied_col(9, 0);
        vector<int> occupied_box(9, 0);
        for (size_t row = 0; row < 9; ++row)
            for (size_t col = 0; col < 9; ++col)
            {
                if (board[row][col] == '.') continue;
                int bitmask = 1 << (board[row][col] - '0' - 1);
                if (occupied_row[row] & bitmask || occupied_col[col] & bitmask ||
                    occupied_box[3 * (row / 3) + (col / 3)] & bitmask)
                    return false;
                occupied_row[row] |= bitmask;
                occupied_col[col] |= bitmask;
                occupied_box[3 * (row / 3) + (col / 3)] |= bitmask;
            }
        return true;
    }
#endif // V2
};