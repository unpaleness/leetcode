#include <forward_list>
#include <vector>

class Solution {
public:
    static void solveSudoku(std::vector<std::vector<char>>& board) {
        std::forward_list<Cell> turns;
        auto nextPoint = getNextEmptyCellCoords(board);
        auto nextCellValueMin = cellValueMin;
        while (!nextPoint.isEmpty()) {
            const auto newValue = getPossibleValue(board, nextPoint, nextCellValueMin);
            if (newValue == cellInvalid) {
                if (turns.empty()) {
                    break;
                }
                const auto last_turn = turns.front();
                nextPoint = last_turn.coords;
                nextCellValueMin = last_turn.value + 1;
                turns.pop_front();
                board[nextPoint.y][nextPoint.x] = cellEmpty;
                continue;
            }
            board[nextPoint.y][nextPoint.x] = newValue;
            turns.push_front({nextPoint, newValue});
            nextCellValueMin = cellValueMin;
            nextPoint = getNextEmptyCellCoords(board);
        }
    }
private:
    static const char cellValueMin{'1'};
    static const char cellValueMax{'9'};
    static const char cellEmpty{'.'};
    static const char cellInvalid{48};
    static const size_t invalidCoord{static_cast<size_t>(-1)};

    struct Point {
        size_t x{invalidCoord};
        size_t y{invalidCoord};
        inline bool isEmpty() const { return x == invalidCoord || y == invalidCoord; }
    };

    struct Cell {
        Point coords;
        char value{0};
    };

    static char getPossibleValue(const std::vector<std::vector<char>>& board, const Point& coords, const char minValue) {
        for (char c = minValue; c <= cellValueMax; ++c) {
            auto shouldSkip = false;
            for (size_t j = 0; j < board.size(); ++j) {
                if (board[j][coords.x] == c) {
                    shouldSkip = true;
                    continue;
                }
            }
            if (shouldSkip) { continue; }
            for (size_t i = 0; i < board[coords.y].size(); ++i) {
                if (board[coords.y][i] == c) {
                    shouldSkip = true;
                    continue;
                }
            }
            if (shouldSkip) { continue; }
            for (size_t j = (coords.y / 3) * 3; j < (coords.y / 3 + 1) * 3; ++j) {
                for (size_t i = (coords.x / 3) * 3; i < (coords.x / 3 + 1) * 3; ++i) {
                    if (board[j][i] == c) {
                        shouldSkip = true;
                        continue;
                    }
                }
            }
            if (shouldSkip) { continue; }
            return c;
        }
        return cellInvalid;
    }

    static Point getNextEmptyCellCoords(const std::vector<std::vector<char>>& board) {
        for (size_t j = 0; j < board.size(); ++j) {
            for (size_t i = 0; i < board.size(); ++i) {
                if (board[j][i] == '.') {
                    return {i, j};
                }
            }
        }
        return {};
    }
};