#include <cstdint>
#include <iostream>
#include <vector>

#include "solution.h"

void checkSolution(const std::vector<std::vector<int32_t>>& lists) {
    std::vector<std::vector<ListNode>> cache;
    cache.reserve(lists.size());
    std::vector<ListNode*> starts;
    starts.reserve(lists.size());
    for (size_t i = 0; i < lists.size(); ++i) {
        const std::vector<int32_t>& list = lists[i];
        std::vector<ListNode> tmp;
        tmp.reserve(list.size());
        for (size_t j = 0; j < list.size(); ++j) {
            ListNode* const last = &tmp.emplace_back(list[j]);
            if (j > 0) {
                tmp[j - 1].next = last;
            }
        }
        cache.push_back(std::move(tmp));
        auto& last = cache.back();
        starts.push_back(last.empty() ? nullptr : &last[0]);
    }
    std::cout << "lists = [";
    for (size_t i = 0; i < cache.size(); ++i) {
        if (i > 0) {
            std::cout << ',';
        }
        std::cout << '[';
        const std::vector<ListNode>& c = cache[i];
        const ListNode* node = c.size() > 0 ? &c[0] : nullptr;
        size_t j = 0;
        while (node) {
            if (j > 0) {
                std::cout << ',';
            }
            std::cout << node->val;
            node = node->next;
            ++j;
        }
        std::cout << ']';
    }
    std::cout << "]\n";

    Solution::mergeKLists(starts);
}

int main() {
    checkSolution({{1,4,5},{1,3,4},{2,6}});
    checkSolution({});
    checkSolution({{}});
    return 0;
}
