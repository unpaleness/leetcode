#include <cstdint>
#include <iostream>
#include <vector>

#include "solution.h"

void checkSolution(const std::vector<int32_t>& list, const int32_t n) {
    std::vector<ListNode> cache;
    cache.reserve(list.size());
    for (size_t i = 0; i < list.size(); ++i) {
        ListNode* const last = &cache.emplace_back(list[i]);
        if (i > 0) {
            cache[i - 1].next = last;
        }
    }
    std::cout << "head = [";
    const ListNode* node = cache.empty() ? nullptr : &cache[0];
    size_t j = 0;
    while (node) {
        if (j > 0) {
            std::cout << ',';
        }
        std::cout << node->val;
        node = node->next;
        ++j;
    }
    std::cout << "], n = " << n << std::endl;

    ListNode* result = Solution::reverseKGroup(cache.empty() ? nullptr : &cache[0], n);

    std::cout << '[';
    size_t i = 0;
    while (result) {
        if (i > 0) {
            std::cout << ',';
        }
        std::cout << result->val;
        result = result->next;
        ++i;
    }
    std::cout << "]\n";
}

int main() {
    checkSolution({1,2,3,4,5}, 2);
    checkSolution({1,2,3,4,5}, 3);
    checkSolution({1,2,3,4}, 4);
    return 0;
}
