#include <string>

class Solution {
public:

    static int romanToInt(const std::string& s) {
        int result{0}, value{0}, rightSymbolValue{0};
        if (!s.empty()) {
            rightSymbolValue = romanFigureToInt(s.back());
            result += rightSymbolValue;
        }
        for (int i = s.size() - 2; i >= 0; --i) {
            value = romanFigureToInt(s[i]);
            result += value < rightSymbolValue ? -value : value;
            rightSymbolValue = value;
        }
        return result;
    }

private:

    static int romanFigureToInt(const char symbol) {
        switch (symbol) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
        }
        return 0;
    }
};