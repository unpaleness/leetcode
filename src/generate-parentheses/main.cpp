#include <iostream>

#include "solution.h"

void checkSolution(const int32_t n) {
    std::cout << std::format("n = {}\n", n);
    std::cout << '[';
    const std::vector<std::string>& solution = Solution::generateParenthesis(n);
    for (size_t i = 0; i < solution.size(); ++i) {
        if (i > 0) {
            std::cout << ',';
        }
        std::cout << std::format("\"{}\"", solution[i]);
    }
    std::cout << "]\n";
}

int main() {
    checkSolution(3);
    checkSolution(1);
    checkSolution(4);
    checkSolution(2);
    return 0;
}
