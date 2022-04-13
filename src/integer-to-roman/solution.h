#include <string>

class Solution {
public:
    static std::string intToRoman(const int num) {
        std::string result;
        char romans[]{'I', 'V', 'X', 'L', 'C', 'D', 'M', '.', ','};
        auto remainder{num};
        for (int i = 3; i >= 0; --i) {
            auto base = Solution::pow(10, i);
            auto quotient = remainder / base;
            if (quotient == 9) {
                result += romans[i * 2];
                result += romans[(i + 1) * 2];
            } else if (quotient > 4) {
                result += romans[i * 2 + 1];
                for (int j = 0; j < quotient - 5; ++j) {
                    result += romans[i * 2];
                }
            } else if (quotient == 4) {
                result += romans[i * 2];
                result += romans[i * 2 + 1];
            } else {
                for (int j = 0; j < quotient; ++j) {
                    result += romans[i * 2];
                }
            }
            remainder -= quotient * base;
        }
        return result;
    }

private:
    static int pow(const int num, const int pow) {
        int result{1};
        for (int i = 0; i < pow; ++i) {
            result *= num;
        }
        return result;
    }
};