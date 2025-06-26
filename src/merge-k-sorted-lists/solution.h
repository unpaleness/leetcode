#include <cstdint>
#include <iostream>
#include <set>
#include <vector>

struct ListNode {
    int32_t val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int32_t x) : val(x), next(nullptr) {}
    ListNode(int32_t x, ListNode* next) : val(x), next(next) {}
};

struct ListNodeComparator {
    bool operator()(const ListNode* a, const ListNode* b) const {
        return a->val < b->val;
    }
};

class Solution {
public:
    static ListNode* mergeKLists(const std::vector<ListNode*>& lists) {
        std::multiset<ListNode*, ListNodeComparator> remaining;
        for (const auto& l : lists) {
            if (l) {
                remaining.insert(l);
            }
        }
        // std::cout << "remaining (init): ";
        // for (const auto& r : remaining) {
        //     std::cout << ' ' << r->val;
        // }
        // std::cout << '\n';
        ListNode* result = nullptr;
        ListNode* current = nullptr;
        while (!remaining.empty()) {
            const auto it = remaining.begin();
            if (current) {
                current->next = *it;
            }
            current = *it;
            if (!result) {
                result = current;
            }
            if (current->next) {
                remaining.insert(current->next);
            }
            remaining.erase(it);
            current->next = nullptr;

            // std::cout << "result: ";
            // ListNode* tmp = result;
            // while (tmp) {
            //     std::cout << ' ' << tmp->val;
            //     tmp = tmp->next;
            // }
            // std::cout << '\n';
            // std::cout << "remaining: ";
            // for (const auto& r : remaining) {
            //     std::cout << ' ' << r->val;
            // }
            // std::cout << '\n';
        }
        return result;
    }
};