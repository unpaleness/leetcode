#include <iostream>
#include <vector>

class Solution {
public:
    static double findMedianSortedArrays(const std::vector<int>& nums1, const std::vector<int>& nums2) {
        if (nums1.size() == 0 && nums2.size() == 0) {
            // std::cout << "both null\n";
            return 0.f;
        }
        if (nums1.size() == 0) {
            if (nums2.size() % 2) {
                // std::cout << "1st null, 2nd odd\n";
                return static_cast<double>(nums2[nums2.size() / 2]);
            } else {
                // std::cout << "1st null, 2nd even\n";
                return (static_cast<double>(nums2[nums2.size() / 2 - 1]) + static_cast<double>(nums2[nums2.size() / 2])) / 2.f;
            }
        }
        if (nums2.size() == 0) {
            if (nums1.size() % 2) {
                // std::cout << "1st odd, 2nd null\n";
                return static_cast<double>(nums1[nums1.size() / 2]);
            } else {
                // std::cout << "1st even, 2nd null\n";
                return (static_cast<double>(nums1[nums1.size() / 2 - 1]) + static_cast<double>(nums1[nums1.size() / 2])) / 2.f;
            }
        }
        int total_size = nums1.size() + nums2.size();
        int i1 = -1;
        int i2 = -1;
        int last_value = -1000000;
        while (i1 + i2 + 2 < total_size / 2 + total_size % 2) {
            if (i1 + 1 < static_cast<int>(nums1.size()) && i2 + 1 < static_cast<int>(nums2.size())) {
                if (nums1[i1 + 1] <= nums2[i2 + 1]) {
                    last_value = nums1[++i1];
                    // std::cout << "both ok, i1 = " << i1 << ", last value = " << last_value << "\n";
                } else {
                    last_value = nums2[++i2];
                    // std::cout << "both ok, i2 = " << i2 << ", last value = " << last_value << "\n";
                }
            } else if (i1 + 1 < static_cast<int>(nums1.size())) {
                last_value = nums1[++i1];
                // std::cout << "1 ok, i1 = " << i1 << ", last value = " << last_value << "\n";
            } else {
                last_value = nums2[++i2];
                // std::cout << "2 ok, i2 = " << i2 << ", last value = " << last_value << "\n";
            }
        }
        if (total_size % 2) {
            // std::cout << "even, return last_value\n";
            return static_cast<double>(last_value);
        } else {
            if (i1 + 1 < static_cast<int>(nums1.size()) && i2 + 1 < static_cast<int>(nums2.size())) {
                if (nums1[i1 + 1] <= nums2[i2 + 1]) {
                    // std::cout << "both ok, i1\n";
                    return static_cast<double>(last_value + nums1[++i1]) / 2.f;
                } else {
                    // std::cout << "both ok, i2\n";
                    return static_cast<double>(last_value + nums2[++i2]) / 2.f;
                }
            } else if (i1 + 1 < static_cast<int>(nums1.size())) {
                // std::cout << "1 ok, i1\n";
                return static_cast<double>(last_value + nums1[++i1]) / 2.f;
            } else {
                // std::cout << "2 ok, i2\n";
                return static_cast<double>(last_value + nums2[++i2]) / 2.f;
            }
        }
    }
};
