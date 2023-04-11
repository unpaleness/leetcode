#include <string>

class Solution {
public:
    static std::string convert(const std::string& s, const size_t numRows) {
        if (numRows <= 1) {
            return s;
        }
        std::string result;
        const auto len = s.size();
        const auto period = (numRows - 1) * 2;
        result.reserve(len);
        for (size_t j = 0; j < numRows; ++j) {
            size_t i = j;
            while (i < len) {
                result += s[i];
                if (j > 0 && j < numRows - 1 && (i + period) - j * 2 < len) {
                    result += s[(i + period) - j * 2];
                }
                i += period;
            }
        }
        return result;
    }
};
