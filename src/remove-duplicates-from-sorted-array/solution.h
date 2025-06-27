#include <vector>

class Solution {
public:
    int32_t removeDuplicates(std::vector<int32_t>& nums) {
        if (nums.empty()) {
            return 0;
        }
        int32_t result = 1;
        size_t offset = 0;
        int32_t max = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) {
            const int32_t val = nums[i];
            if (val == max) {
                ++offset;
            } else {
                ++result;
                max = val;
                nums[i - offset] = val;
            }
        }
        return result;
    }
};
