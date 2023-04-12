#include <limits>
#include <string>

class Solution {
public:
    static int32_t myAtoi(const std::string& s) {
        int32_t result{0};
        int32_t sign{1};
        char cPrev{' '};
        for (const auto c : s) {
            if (isDigit(c)) {
                int32_t digit = static_cast<int32_t>(c - 0x30) * sign;
                if (result > std::numeric_limits<int32_t>::max() / 10 ||
                    (result == std::numeric_limits<int32_t>::max() / 10 && digit > 7)) {
                    return std::numeric_limits<int32_t>::max();
                }
                if (result < std::numeric_limits<int32_t>::min() / 10 ||
                    (result == std::numeric_limits<int32_t>::min() / 10 && digit < -8)) {
                    return std::numeric_limits<int32_t>::min();
                }
                result = result * 10 + digit;
            } else if (isDigit(cPrev) || (c != ' ' && c != '-' && c != '+') ||
                       ((c == '+' || c == '-') && cPrev != ' ') || (c == ' ' && cPrev != ' ')) {
                return result;
            } else {
                if (c == '-') {
                    sign = -1;
                }
            }
            cPrev = c;
        }
        return result;
    };

private:
    static inline bool isDigit(const char c) { return c >= 0x30 && c <= 0x39; }
};
