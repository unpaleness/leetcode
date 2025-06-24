#include <cstdint>
#include <iostream>
#include <vector>

#include "solution.h"

void checkSolution(const std::initializer_list<int32_t>& init, const int32_t n) {
    std::vector<ListNode> tmp;
    tmp.reserve(init.size());
    ListNode* last = nullptr;
    std::cout << "head = [";
    for (const auto val : init) {
        auto* const node = &tmp.emplace_back(val);
        if (last) {
            std::cout << ',';
            last->next = node;
        }
        std::cout << val;
        last = node;
    }
    std::cout << "], n = " << n << std::endl;

    ListNode* newHead = Solution::removeNthFromEnd(tmp.empty() ? nullptr : &tmp[0], n);

    std::cout << "result = [";
    size_t i = 0;
    while (newHead) {
        if (i > 0) {
            std::cout << ',';
        }
        std::cout << newHead->val;
        newHead = newHead->next;
        ++i;
    }
    std::cout << ']' << std::endl;
}

int main() {
    checkSolution({1, 2, 3, 4, 5}, 2);
    return 0;
}
