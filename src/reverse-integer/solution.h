#include <string>
#include <vector>

class Solution {
public:
    static int32_t reverse(const int32_t x) {
        // std::cerr << "x: " << x << std::endl;
        if (x == static_cast<int32_t>(0x80000000)) {
            return 0;
        }
        const int32_t sign{x < 0 ? static_cast<int32_t>(-1) : static_cast<int32_t>(1)};
        const int32_t ethalon{sign < 0 ? static_cast<int32_t>(0x80000000) : static_cast<int32_t>(0x7FFFFFFF)};
        int32_t divider{1000000000};
        int32_t tmp{x * sign};
        int32_t result{0};
        auto isEdge = tmp >= 1000000000;
        while (tmp > 0) {
            // std::cerr << "tmp: " << tmp << ", isEdge: " << isEdge;
            if (isEdge) {
                int32_t ethalonDigit = ((ethalon / divider) % 10) * sign;
                // std::cerr << ", e: " << ethalonDigit;
                if (tmp % 10 > ethalonDigit) {
                    // std::cerr << ", " << tmp % 10 << " > " << ethalonDigit << std::endl;
                    return 0;
                } else if (tmp % 10 < ethalonDigit) {
                    // std::cerr << ", " << tmp % 10 << " < " << ethalonDigit;
                    isEdge = false;
                }
            }
            result *= 10;
            result += tmp % 10;
            tmp /= 10;
            divider /= 10;
            // std::cerr << std::endl;
        }
        return result * sign;
    }
};
