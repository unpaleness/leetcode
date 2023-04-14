#include <iostream>

#include "solution.h"

int main() {
    std::cout << Solution::isMatch("aa", "a") << std::endl;
    std::cout << Solution::isMatch("aa", "a*") << std::endl;
    std::cout << Solution::isMatch("ab", ".*") << std::endl;
    std::cout << Solution::isMatch("alflflbde", "a.*bc*d.*e.*") << std::endl;
    std::cout << Solution::isMatch("aaa", "a.*aa") << std::endl;
    std::cout << Solution::isMatch("ab", ".*c") << std::endl;
    return 0;
}
