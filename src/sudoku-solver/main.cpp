#include <iostream>
#include <vector>

#include "solution.h"

void output(const std::vector<std::vector<char>>& board) {
    for (size_t j = 0; j < board.size(); ++j) {
        if (j % 3 == 0) {
            std::cout << std::endl;
        }
        for (size_t i = 0; i < board[j].size(); ++i) {
            if (i % 3 == 0) {
                std::cout << "  ";
            }
            std::cout << ' ' << board[j][i];
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<std::vector<char>> board{{'5','3','.','.','7','.','.','.','.'},{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'}};

    output(board);

    Solution::solveSudoku(board);

    output(board);

    return 0;
}
