#include <iostream>

#include "solution.h"

void output_and_clean(ListNode* a) {
    auto* itA = a;
    while (itA) {
        std::cout << itA->val;
        auto* tmp = itA->next;
        delete itA;
        itA = tmp;
    }
    std::cout << std::endl;
}

int main() {
    auto* a = new ListNode(2, new ListNode(4, new ListNode(3)));
    auto* b = new ListNode(5, new ListNode(6, new ListNode(4)));

    auto* c = Solution::addTwoNumbers(a, b);

    output_and_clean(a);
    output_and_clean(b);
    output_and_clean(c);

    return 0;
}
