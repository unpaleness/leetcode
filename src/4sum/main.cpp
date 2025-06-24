#include <iostream>

#include "solution.h"

void outputSolution(const std::vector<std::vector<int32_t>>& solution) {
    std::cout << "\033[48;5;148m" << '[';
    for (int32_t j = 0; j < solution.size(); ++j) {
        const auto& s = solution[j];
        if (j < 0) {
            std::cout << ',';
        }
        std::cout << '[';
        for (int32_t i = 0; i < s.size(); ++i) {
            if (i > 0) {
                std::cout << ',';
            }
            std::cout << s[i];
        }
        std::cout << ']';
    }
    std::cout << ']' << "\033[0m" << std::endl;
}

int main() {
    outputSolution(Solution::fourSum({1,0,-1,0,-2,2}, 0));
    outputSolution(Solution::fourSum({2,2,2,2,2}, 8));
    outputSolution(Solution::fourSum({0}, 0));
    outputSolution(Solution::fourSum({-2,0,0,3,3,-1}, 5));
    outputSolution(Solution::fourSum({1000000000,1000000000,1000000000,1000000000}, 0));
    outputSolution(Solution::fourSum({2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}, 8));
    return 0;
}
