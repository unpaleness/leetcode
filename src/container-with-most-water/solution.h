#include <iostream>
#include <vector>

class Solution {
public:
    static int maxArea(const std::vector<int>& heights) {
        int result{0};
        int i1{0};
        int i2{static_cast<int>(heights.size() - 1)};
        while (i1 < i2) {
            result = std::max(result, std::min(heights[i1], heights[i2]) * (i2 - i1));
            if (heights[i1] > heights[i2]) {
                --i2;
            } else {
                ++i1;
            }
        }
        return result;
    }
};
