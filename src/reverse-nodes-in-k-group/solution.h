#include <cstdint>

struct ListNode {
    int32_t val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int32_t x) : val(x), next(nullptr) {}
    ListNode(int32_t x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    static ListNode* reverseKGroup(ListNode* head, const int32_t k) {
        if (k < 2) {
            return head;
        }
        ListNode* it = head;
        ListNode* prev = nullptr;
        ListNode* result = head;
        while (it) {
            ListNode* begin = it;
            ListNode* end = it;
            size_t i = 0;
            while (it && i < k) {
                end = it;
                it = it->next;
                ++i;
            }
            if (i == k) {
                ListNode* prev2 = nullptr;
                ListNode* it2 = begin;
                ListNode* afterEnd = end->next;
                while (it2 != afterEnd) {
                    ListNode* oldNext = it2->next;
                    prev2 ? it2->next = prev2 : it2->next = afterEnd;
                    prev2 = it2;
                    it2 = oldNext;
                }
                if (prev) {
                    prev->next = end;
                } else {
                    result = end;
                }
            }
            prev = begin;
        }
        return result;
    }
};
