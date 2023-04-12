#include <iostream>

#include "solution.h"

int main() {
    std::cout << Solution::myAtoi("42") << std::endl;
    std::cout << Solution::myAtoi("   -42") << std::endl;
    std::cout << Solution::myAtoi("4193 with words") << std::endl;
    std::cout << Solution::myAtoi("words and 987") << std::endl;
    return 0;
}
