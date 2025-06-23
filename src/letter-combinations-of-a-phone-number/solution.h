#include <string>
#include <vector>

class Solution {
public:
    static std::vector<std::string> letterCombinations(const std::string& digits) {
        std::vector<std::string> combinations;
        iterate(0, digits, "", combinations);
        return std::move(combinations);
    }
private:
    static std::string letters(const char c) {
        switch (c) {
            case '2': return "abc";
            case '3': return "def";
            case '4': return "ghi";
            case '5': return "jkl";
            case '6': return "mno";
            case '7': return "pqrs";
            case '8': return "tuv";
            case '9': return "wxyz";
            default: return "";
        }
    }
    static void iterate(const size_t depth, const std::string& digits, const std::string& result, std::vector<std::string>& combinations) {
        for (const auto c : letters(digits[depth])) {
            if (depth < digits.size() - 1) {
                iterate(depth + 1, digits, result + c, combinations);
            } else {
                combinations.push_back(result + c);
            }
        }
    }
};
