#include <iostream>

#include "solution.h"

int main() {
    std::cout << "Hello" << std::endl;
    std::cout << Solution::longestPalindrome("babad") << std::endl;
    std::cout << Solution::longestPalindrome("abbc") << std::endl;
    std::cout << "Hello" << std::endl;

    return 0;
}
