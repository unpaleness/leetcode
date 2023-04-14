#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    static bool isMatch(const std::string& s, const std::string& p) {
        std::cerr << "s: " << s << ", p: " << p << std::endl;
        std::vector<Group> groups;
        for (size_t i = 0; i < p.size(); ++i) {
            const auto c = p[i];
            if (isLetter(c)) {
                if (groups.empty() || groups.back().isMulti || groups.back().isWild ||
                    (i < p.size() - 1 && p[i + 1] == '*')) {
                    groups.emplace_back(Group{std::string(1, c)});
                } else {
                    groups.back().substr += c;
                }
            } else if (c == '.') {
                groups.emplace_back(Group{"", true});
            } else {
                if (!groups.empty()) {
                    groups.back().isMulti = true;
                }
            }
        }
        for (const auto& g : groups) {
            std::cerr << g << std::endl;
        }
        return doesMatch(s, groups, 0, 0);
    }

private:
    struct Group {
        std::string substr;
        bool isWild{false};
        bool isMulti{false};
        friend std::ostream& operator<<(std::ostream& out, const Group& g) {
            return out << "{" << (g.isWild ? "." : g.substr) << (g.isMulti ? "*" : "") << "}";
        }
    };

    static inline bool isLetter(const char c) { return c >= 0x61 && c <= 0x7a; }
    static inline bool doesMatch(const std::string& s,
                                 const std::vector<Group>& groups,
                                 const size_t sIndex,
                                 const size_t gIndex) {
        if (sIndex == s.size() && gIndex == groups.size()) {  // string and groups are both over
            return true;
        }
        if (sIndex >= s.size() || gIndex >= groups.size()) {
            std::cerr << sIndex << " >= " << s.size() << " || " << gIndex << " >= " << groups.size() << std::endl;
            return false;
        }
        std::cerr << std::string(sIndex, ' ') << s.substr(sIndex) << " " << groups[gIndex] << std::endl;
        const auto& g = groups[gIndex];
        if (!g.isMulti) {
            if (!g.isWild) {
                if (g.substr != s.substr(sIndex, g.substr.size())) {
                    return false;
                }
                return doesMatch(s, groups, sIndex + g.substr.size(), gIndex + 1);
            } else {
                // skip
                return doesMatch(s, groups, sIndex + 1, gIndex + 1);
            }
        } else {
            if (!g.isWild) {
                if (doesMatch(s, groups, sIndex, gIndex + 1)) {
                    return true;
                }
                size_t i = sIndex;
                while (i < s.size() && s[i] == g.substr[0]) {
                    if (doesMatch(s, groups, i + 1, gIndex + 1)) {
                        return true;
                    }
                    ++i;
                }
                return false;
            } else {
                for (size_t i = sIndex; i < s.size(); ++i) {
                    if (doesMatch(s, groups, i, gIndex + 1)) {
                        return true;
                    }
                }
                return false;
            }
        }
    }
};
