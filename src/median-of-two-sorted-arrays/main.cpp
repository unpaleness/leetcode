#include <iostream>
#include <vector>

#include "solution.h"

int main() {
    std::vector<int> a = {1,3};
    std::vector<int> b = {2};
    std::cout << Solution::findMedianSortedArrays(a, b) << std::endl;
    return 0;
}