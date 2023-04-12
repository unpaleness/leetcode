#include <iostream>

#include "solution.h"

int main() {
    std::cout << Solution::reverse(123) << std::endl;
    std::cout << Solution::reverse(-123) << std::endl;
    std::cout << Solution::reverse(120) << std::endl;
    std::cout << Solution::reverse(1563847412) << std::endl;
    std::cout << Solution::reverse(-1463847412) << std::endl;
    return 0;
}
