#include <algorithm>
#include <cstdint>
#include <vector>

class Solution {
public:
    // O(n^2)
    static std::vector<std::vector<int32_t>> threeSum(std::vector<int32_t>& nums) {
        if (nums.size() < 3) {
            return {};
        }
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int32_t>> result;
        const size_t s = nums.size();
        size_t i1 = 0;
        do {
            const int32_t v1 = nums[i1];
            size_t i2 = i1 + 1;
            size_t i3 = s - 1;
            do {
                const int32_t v2 = nums[i2];
                const int32_t v3 = nums[i3];
                const int32_t sum = v1 + v2 + v3;
                if (sum == 0) {
                    result.push_back({v1, v2, v3});
                    do {
                        ++i2;
                    } while (nums[i2] == v2 && i2 < i3);
                    do {
                        --i3;
                    } while (nums[i3] == v3 && i2 < i3);
                } else if (sum < 0) {
                    do {
                        ++i2;
                    } while (nums[i2] == v2 && i2 < i3);
                } else {
                    do {
                        --i3;
                    } while (nums[i3] == v3 && i2 < i3);
                }
            } while (i2 < i3);
            do {
                ++i1;
            } while (nums[i1] == v1 && i1 < s - 2);
        } while (i1 < s - 2);
        return result;
    }
};
