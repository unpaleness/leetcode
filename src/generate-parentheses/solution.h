#include <cstdint>
#include <format>
#include <string>
#include <vector>

class Solution {
public:
    static std::vector<std::string> generateParenthesis(const int32_t n) {
        if (n <= 0) {
            return {};
        }
        std::vector<std::string> results;
        std::string tmp_result(n * 2, ' ');
        iterate(n, 0, 0, tmp_result, results);
        return std::move(results);
    }

private:
    static void iterate(const int32_t n, const int32_t i, const int32_t opened_count, std::string& tmp_result, std::vector<std::string>& results) {
        if (i < n * 2)
        {
            if (opened_count < n && opened_count < n * 2 - i) {
                tmp_result[i] = '(';
                iterate(n, i + 1, opened_count + 1, tmp_result, results);
            }
            if (opened_count > 0) {
                tmp_result[i] = ')';
                iterate(n, i + 1, opened_count - 1, tmp_result, results);
            }
        } else {
            results.push_back(tmp_result);
        }
    }
};
