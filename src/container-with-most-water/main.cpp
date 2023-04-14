#include <iostream>

#include "solution.h"

int main() {
    std::cout << Solution::maxArea({1, 8, 6, 2, 5, 4, 8, 3, 7}) << std::endl;
    std::cout << Solution::maxArea({1, 1}) << std::endl;
    std::cout << Solution::maxArea({1, 3, 2, 5, 25, 24, 5}) << std::endl;
    return 0;
}
