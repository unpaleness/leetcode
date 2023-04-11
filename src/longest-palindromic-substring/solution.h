#include <string>

class Solution {
public:
    static std::string longestPalindrome(const std::string& s) {
        int32_t posBegin{0};
        int32_t posEnd{0};
        for (size_t i = 0; i < s.size(); ++i) {
            int32_t tmpPosBegin{0};
            int32_t tmpPosEnd{0};
            getPalindromeFromCenterPos(s, i, false, tmpPosBegin, tmpPosEnd);
            if (tmpPosEnd - tmpPosBegin > posEnd - posBegin) {
                posBegin = tmpPosBegin;
                posEnd = tmpPosEnd;
            }
            getPalindromeFromCenterPos(s, i, true, tmpPosBegin, tmpPosEnd);
            if (tmpPosEnd - tmpPosBegin > posEnd - posBegin) {
                posBegin = tmpPosBegin;
                posEnd = tmpPosEnd;
            }
        }
        return s.substr(posBegin, posEnd + 1 - posBegin);
    }

private:
    static void getPalindromeFromCenterPos(const std::string& s,
                                           const int32_t i,
                                           const bool isEven,
                                           int32_t& posBegin,
                                           int32_t& posEnd) {
        posBegin = i;
        posEnd = i;
        if (i < 0 || i >= s.size()) {
            return;
        }
        if (isEven) {
            if (i + 1 >= s.size() || s[i] != s[i + 1]) {
                return;
            }
            posEnd = i + 1;
        }
        while (posBegin >= 0 && posEnd < s.size() && s[posBegin] == s[posEnd]) {
            --posBegin;
            ++posEnd;
        }
        ++posBegin;
        --posEnd;
    }
};
