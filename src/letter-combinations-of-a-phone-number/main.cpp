#include <iostream>

#include "solution.h"

void output(const std::vector<std::string>& result) {
    std::cout << '[';
    for (size_t i = 0; i < result.size(); ++i) {
        if (i > 0) {
            std::cout << ',';
        }
        std::cout << '"' << result[i] << '"';
    }
    std::cout << ']' << std::endl;
}

int main() {
    output(Solution::letterCombinations("23"));
    output(Solution::letterCombinations(""));
    output(Solution::letterCombinations("2"));
    return 0;
}
