#include "listnode.h"

class Solution {
public:
    static ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        auto* result = new ListNode();
        auto* itResult = result;
        auto* itL1 = l1;
        auto* itL2 = l2;
        while (itL1 || itL2) {
            if (itL1) {
                itResult->val += itL1->val;
                itL1 = itL1->next;
            }
            if (itL2) {
                itResult->val += itL2->val;
                itL2 = itL2->next;
            }
            if (itL1 || itL2 || itResult->val > 9) {
                itResult->next = new ListNode();
                if (itResult->val > 9) {
                    itResult->val -= 10;
                    itResult->next->val = 1;
                }
                itResult = itResult->next;
            }
        }
        return result;
    }
};