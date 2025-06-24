#include <string>

class Solution {
public:
    static bool isValid(const std::string& s) {
        std::string cache;
        size_t depth { 0 };
        for (const auto c : s) {
            if (c == '(' || c == '[' || c == '{') {
                ++depth;
                cache.push_back(c);
            } else if (cache.empty()) {
                return false;
            }
            if (c == ')') {
                if (cache.back() == '(') {
                    cache.pop_back();
                    --depth;
                } else {
                    return false;
                }
            }
            if (c == ']') {
                if (cache.back() == '[') {
                    cache.pop_back();
                    --depth;
                } else {
                    return false;
                }
            }
            if (c == '}') {
                if (cache.back() == '{') {
                    cache.pop_back();
                    --depth;
                } else {
                    return false;
                }
            }
        }
        return cache.empty();
    }
};