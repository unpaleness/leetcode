class Solution {
public:
    static bool isPalindrome(const int32_t x) {
        auto tmp = x;
        int64_t xMirrored{0};
        while (tmp > 0) {
            xMirrored = xMirrored * 10 + tmp % 10;
            tmp /= 10;
        }
        return x == xMirrored;
    }
};
