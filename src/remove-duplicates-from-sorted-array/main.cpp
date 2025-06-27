#include <cstdint>
#include <iostream>
#include <vector>

#include "solution.h"

void checkSolution(const std::vector<int32_t>& nums) {
    std::vector<int32_t> result = nums;
    std::cout << "nums = [";
    for (size_t i = 0; i < result.size(); ++i) {
        if (i > 0) {
            std::cout << ',';
        }
        std::cout << result[i];
    }
    std::cout << ']' << std::endl;

    Solution solution;
    const auto n = solution.removeDuplicates(result);

    std::cout << n << ", nums = [";
    for (size_t i = 0; i < result.size(); ++i) {
        if (i > 0) {
            std::cout << ',';
        }
        std::cout << result[i];
    }
    std::cout << ']' << std::endl;
}

int main() {
    checkSolution({1,1,2});
    checkSolution({0,0,1,1,1,2,2,3,3,4});
    return 0;
}
