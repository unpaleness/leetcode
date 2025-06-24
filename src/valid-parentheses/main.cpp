#include <iostream>

#include "solution.h"

void checkSolution(const std::string& s) {
    std::cout << "s = " << s << std::endl;
    std::cout << (Solution::isValid(s) ? "true" : "false") << std::endl;
}

int main() {
    checkSolution("()");
    checkSolution("()[]{}");
    checkSolution("(]");
    checkSolution("([])");
    checkSolution("[");
    return 0;
}
