#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

class Solution {
public:
    static std::vector<std::vector<int32_t>> threeSum(std::vector<int32_t>& nums) {
        std::unordered_map<int32_t, std::vector<size_t>> values;
        for (size_t i = 0; i < nums.size(); ++i) {
            auto it = values.find(nums[i]);
            if (it == values.end()) {
                values.emplace(nums[i], std::vector<size_t>{i});
            } else {
                it->second.push_back(i);
            }
        }
        std::vector<std::vector<int32_t>> result;
        // tree.print();
        for (const auto& pair1 : values) {
            for (const auto& pair2 : values) {
                int32_t v1 = pair1.first;
                int32_t v2 = pair2.first;
                int32_t v3 = - v1 - v2;
                // we should skip if there's only one element with such a value
                if (v1 == v2 && pair1.second.size() < 2) {
                    continue;
                }
                const auto it = values.find(v3);
                // we should skip if no element with such value
                if (it == values.end()) {
                    continue;
                }
                // we should skip if there's only one element with such a value
                if ((v3 == v1 || v3 == v2) && it->second.size() < (v1 == v2 ? 3 : 2)) {
                    continue;
                }
                if (v2 < v1) {
                    std::swap(v1, v2);
                }
                if (v3 < v1) {
                    std::swap(v1, v3);
                }
                if (v3 < v2) {
                    std::swap(v2, v3);
                }
                bool is_unique = true;
                for (const auto& r : result) {
                    if (v1 == r[0] && v2 == r[1] && v3 == r[2]) {
                        is_unique = false;
                        break;
                    }
                }
                // we should skip if tuple is not unique
                if (!is_unique) {
                    continue;
                }
                result.push_back({v1, v2, v3});
            }
        }
        return result;
    }
};
