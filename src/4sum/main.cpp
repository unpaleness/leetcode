#include <iostream>

#include "solution.h"

void outputSolution(const std::vector<std::vector<int32_t>>& solution) {
    std::cout << '[';
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
    std::cout << ']' << std::endl;
}

int main() {
    std::vector<int32_t> v;
    v = {1,0,-1,0,-2,2};
    outputSolution(Solution::fourSum(v, 0));
    return 0;
}
