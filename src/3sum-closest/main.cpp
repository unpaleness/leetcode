#include <iostream>

#include "solution.h"

int main() {
    std::vector<int32_t> v;
    v = {-1,2,1,-4};
    std::cout << Solution::threeSumClosest(v, 1) << std::endl;
    v = {0,0,0};
    std::cout << Solution::threeSumClosest(v, 1) << std::endl;
    return 0;
}
