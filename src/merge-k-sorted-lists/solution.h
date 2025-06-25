#include <cstdint>
#include <iostream>
#include <vector>
#include <set>

struct ListNode {
    int32_t val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int32_t x) : val(x), next(nullptr) {}
    ListNode(int32_t x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    static ListNode* mergeKLists(const std::vector<ListNode*>& lists) {
        std::set<ListNode*> remaining;
        for (const auto& l : lists) {
            if (l) {
                remaining.insert(l);
            }
        }
        for (const auto& r : remaining) {
            std::cout << ' ' << r->val;
        }
        std::cout << '\n';
        ListNode* result = nullptr;
        // while (!remaining.empty()) {
        //     // erase first element and push it to result
        // }
        return result;
    }
};