class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.size() > haystack.size()) {
            return -1;
        }
        const size_t n1 = haystack.size();
        const size_t n2 = needle.size();
        for (size_t i = 0; i <= n1 - n2; ++i) {
            bool is_ok = true;
            for (size_t j = 0; j < n2; ++j) {
                if (needle[j] != haystack[i + j]) {
                    is_ok = false;
                    break;
                }
            }
            if (is_ok) {
                return i;
            }
        }
        return -1;
    }
};
